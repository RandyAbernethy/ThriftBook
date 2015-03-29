TARGET = client server
IDL = inherit.thrift
SVRSRC = inherit_server.cpp gen-cpp/SocialUpdate.cpp gen-cpp/SocialLookup.cpp
CLISRC = inherit_client.cpp gen-cpp/SocialUpdate.cpp gen-cpp/SocialLookup.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -r -gen cpp

all: client server

gen-cpp/SocialUpdate.cpp gen-cpp/SocialLookup.cpp: $(IDL)
	$(THRIFT) $(IDL)

server: $(SVRSRC)
	$(CC) -o $@ $(SVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
