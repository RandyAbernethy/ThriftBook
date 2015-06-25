TARGET = bin_file_write bin_mem proto_write_times
BINSRC = bin_file_write.cpp
MEMSRC = bin_mem.cpp
PROTOSRC = proto_write_times.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11

all: bin_file_write bin_mem proto_write_times

bin_file_write: $(BINSRC)
	$(CC) -o $@ $(BINSRC) $(CFLAGS) $(LIBS)

bin_mem: $(MEMSRC)
	$(CC) -o $@ $(MEMSRC) $(CFLAGS) $(LIBS)
	
proto_write_times: $(PROTOSRC)
	$(CC) -o $@ $(PROTOSRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) $(TARGET)
	$(RM) data
