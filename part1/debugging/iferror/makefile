TARGET = client
IDL = hello_name.thrift
CLISRC = hello_client_new.cpp gen-cpp/HelloSvc.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: client

gen-cpp/HelloSvc.cpp: $(IDL)
	$(THRIFT) $(IDL)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
