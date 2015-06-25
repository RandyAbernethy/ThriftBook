TARGET = server client
SVRSRC = server_frame.cpp
CLISRC = client_frame.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: server client

server: $(SVRSRC)
	$(CC) -o $@ $(SVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) $(TARGET)
