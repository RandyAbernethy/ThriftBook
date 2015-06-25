TARGET = client client2 server
IDL = simple.thrift
SVRSRC = event_server.cpp gen-cpp/Message.cpp
CLISRC = event_client.cpp gen-cpp/Message.cpp
CLI2SRC = event_client2.cpp gen-cpp/Message.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: client client2 server

gen-cpp/Message.cpp: $(IDL)
	$(THRIFT) $(IDL)

server: $(SVRSRC)
	$(CC) -o $@ $(SVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
client2: $(CLI2SRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)

clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
