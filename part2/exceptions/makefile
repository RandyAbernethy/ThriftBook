TARGET = client server trans_excep
IDL = excep.thrift
SVRSRC = excep_server.cpp gen-cpp/TradeHistory.cpp gen-cpp/excep_types.cpp
CLISRC = excep_client.cpp gen-cpp/TradeHistory.cpp gen-cpp/excep_types.cpp
TESRC = trans_excep.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: client server trans_excep

gen-cpp/TradeHistory.cpp gen-cpp/excep_types.cpp: $(IDL)
	$(THRIFT) $(IDL)

server: $(SVRSRC)
	$(CC) -o $@ $(SVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
trans_excep: $(TESRC)
	$(CC) -o $@ $(TESRC) $(CFLAGS) $(LIBS)

clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
	$(RM) data
