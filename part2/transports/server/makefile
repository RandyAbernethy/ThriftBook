TARGET = server_trans
SRC = server_trans.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11

all: server_trans

server_trans: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) $(TARGET)
