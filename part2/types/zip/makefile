TARGET = disk_ser_z
IDL = radio_observation.thrift
SRC = disk_ser_z.cpp gen-cpp/*.cpp

CC = g++
LIBS = -lthrift -lthriftz -lz
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: disk_ser_z

gen-cpp/*.cpp: $(IDL)
	$(THRIFT) $(IDL)

disk_ser_z: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)

clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
