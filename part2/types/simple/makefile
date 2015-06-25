TARGET = udt
IDL = simple_udt.thrift
SRC = simple_udt.cpp gen-cpp/simple_udt_types.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: udt

gen-cpp/simple_udt_types.cpp: $(IDL)
	$(THRIFT) $(IDL)

udt: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)

clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
