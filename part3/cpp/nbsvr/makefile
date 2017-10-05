TARGET = server client
IDL = trade_report.thrift
SVRSRC = nb_server.cpp gen-cpp/TradeHistory.cpp gen-cpp/trade_report_types.cpp
CLISRC = nb_client.cpp gen-cpp/TradeHistory.cpp gen-cpp/trade_report_types.cpp

CC = g++
LIBS = -lthrift -lthriftnb -levent -lpthread
CFLAGS = -Wall -std=c++11
THRIFT = thrift -gen cpp

all: server client

gen-cpp/TradeHistory.cpp: $(IDL)
	$(THRIFT) $(IDL)

gen-cpp/trade_report_types.cpp: $(IDL)
	$(THRIFT) $(IDL)

server: $(SVRSRC)
	$(CC) -o $@ $(SVRSRC) $(CFLAGS) $(LIBS)

client: $(CLISRC)
	$(CC) -o $@ $(CLISRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) -r gen-cpp
	$(RM) $(TARGET)
