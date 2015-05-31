TARGET = nvi_server vi_server client
SIDL = nvi.thrift
NVISVRSRC = nvi_server.cpp gen-cpp/NVITest.cpp gen-cpp/nvi_types.cpp
VISVRSRC = vi_server.cpp gen-cpp/NVITest.cpp gen-cpp/nvi_types.cpp
CLISRC = client.cpp gen-cpp/NVITest.cpp gen-cpp/nvi_types.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: nvi_server vi_server client

gen-cpp/nvi_types.cpp: $(SIDL)
	$(THRIFT) $(SIDL)

gen-cpp/NVITest.cpp: $(SIDL)
	$(THRIFT) $(SIDL)

nvi_server: $(NVISVRSRC)
	$(CC) -o $@ $(NVISVRSRC) $(CFLAGS) $(LIBS)

vi_server: $(VISVRSRC)
	$(CC) -o $@ $(VISVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
