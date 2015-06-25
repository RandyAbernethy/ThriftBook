TARGET = mem_trans
SRC = mem_trans.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11

all: mem_trans

mem_trans: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) $(TARGET)
