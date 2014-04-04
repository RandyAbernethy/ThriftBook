#ifndef _MY_SERVER_EVENT_HANDLER_H_
#define _MY_SERVER_EVENT_HANDLER_H_ 1

#include <sstream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TTransport.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/server/TServer.h>

class PoolSvrEvtHandler : public apache::thrift::server::TServerEventHandler {
public:
    PoolSvrEvtHandler(boost::shared_ptr<apache::thrift::concurrency::ThreadManager> thread_man, 
                     unsigned int thread_min, unsigned int thread_max) : 
        t_man(thread_man), t_min(thread_min), t_max(thread_max)
    {;}

    std::string stats(int reduce_in_use_by=0) {
       std::stringstream ss;
       ss << "(threads in use: " << t_man->workerCount() - t_man->idleWorkerCount() - reduce_in_use_by
          << "/" << t_man->workerCount() << " - connections waiting: " << t_man->pendingTaskCount() << ")";
       return ss.str();
    }
    
    virtual void preServe() override {
        std::cout << "  preServe " << stats() << std::endl;
    }

    virtual void* createContext(boost::shared_ptr<apache::thrift::protocol::TProtocol> in,
                                boost::shared_ptr<apache::thrift::protocol::TProtocol> out) override {
        std::cout << "  create   " << stats() << std::endl;
        if (t_man->idleWorkerCount() == 0 && t_man->workerCount() < t_max) {
            t_man->addWorker();
            std::cout << "    No idle threads, added a new worker thread\n           " << stats() << std::endl; 
        }
        return new int(0);
    }

    virtual void deleteContext(void* svr_ctx, 
                               boost::shared_ptr<apache::thrift::protocol::TProtocol> in,
                               boost::shared_ptr<apache::thrift::protocol::TProtocol> out) override {
        std::cout << "  delete   " << stats(1) << std::endl;
        if (t_man->idleWorkerCount() >= t_man->workerCount()/2 && t_man->workerCount() > t_min) {
            t_man->removeWorker();
            std::cout << "    Too many idle threads, deleted a worker thread\n           " << stats(1) << std::endl; 
        }
        int * pCallCount = reinterpret_cast<int *>(svr_ctx);
        delete pCallCount;
    }

    virtual void processContext(void* svr_ctx, boost::shared_ptr<apache::thrift::transport::TTransport> trans) override {
        int * call_count = reinterpret_cast<int *>(svr_ctx);
        std::cout << "    Client call #" << ++(*call_count) << std::endl;       
    }

private:
    boost::shared_ptr<apache::thrift::concurrency::ThreadManager> t_man;
    unsigned int t_min;
    unsigned int t_max;
};

#endif //_MY_SERVER_EVENT_HANDLER_H_
