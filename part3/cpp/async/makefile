TARGET = server client
IDL = hello.thrift
SVRSRC = hello_server.cpp gen-cpp/helloSvc.cpp
CLISRC = async_client.cpp gen-cpp/helloSvc.cpp

CC = g++
LIBS = -lthrift -lpthread
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: server client

gen-cpp/helloSvc.cpp: $(IDL)
	$(THRIFT) $(IDL)

server: $(SVRSRC)
	$(CC) -o $@ $(SVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
