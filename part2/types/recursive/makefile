TARGET = server client
IDL = tree.thrift
SVRSRC = server.cpp gen-cpp/simple.cpp gen-cpp/tree_types.cpp
CLISRC = client.cpp gen-cpp/simple.cpp gen-cpp/tree_types.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: server client

gen-cpp/simple.cpp: $(IDL)
	$(THRIFT) $(IDL)

gen-cpp/tree_types.cpp: $(IDL)
	$(THRIFT) $(IDL)

server: $(SVRSRC)
	$(CC) -o $@ $(SVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
