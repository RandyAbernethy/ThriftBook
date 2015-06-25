TARGET = sock_trans
SRC = sock_trans.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11

all: sock_trans

sock_trans: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) $(TARGET)
