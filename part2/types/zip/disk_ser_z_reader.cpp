// ZLib serialization compression

#include <iostream>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/transport/TZlibTransport.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/radio_observation_types.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace radio_observation;

void DumpRadioObservation(const RadioObservation & ro) {
    auto it = _RadioObservationSystem_VALUES_TO_NAMES.find(ro.system);
    auto psystem = (std::end(_RadioObservationSystem_VALUES_TO_NAMES) == it) ? "" : it->second;
    std::cout << "\nRadio Observation"
              << "\n-------------------------"
              << "\nTelescope Count: " << ro.telescope_count 
              << "\nSystem         : " << psystem
              << "\nTime           : " << ro.time 
              << "\nPosition       : ";
    if (ro.pos.__isset.icrfpos) {
        std::cout << ro.pos.icrfpos.declination << " dec - " 
                  << ro.pos.icrfpos.right_ascension << " ra [";
        if (ro.pos.icrfpos.__isset.ecliptic_year)
            std::cout << ro.pos.icrfpos.ecliptic_year;
        std::cout << "]";
    }
    std::cout << "\nFrequency   Magnitude\n";
    for (auto it : ro.freq_amp) 
        std::cout << "  " << it.first << "  " << it.second << "\n";
    std::cout << "Size of bmp: " << ((ro.__isset.sky_bmp) ? ro.sky_bmp.length() : 0) << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return -1;
    }
    try {
		std::cout << "Reading from compressed file: " << argv[1] << std::endl;
		boost::shared_ptr<TSimpleFileTransport> ep_trans(new TSimpleFileTransport(argv[1], true, true));
		boost::shared_ptr<TZlibTransport> z_trans(new TZlibTransport(ep_trans));
		z_trans->open();
		std::unique_ptr<TProtocol> proto(new TBinaryProtocol(z_trans));
		RadioObservation ro;
		ro.read(proto.get());
		z_trans->close();
		DumpRadioObservation(ro);
    } catch (std::exception ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

