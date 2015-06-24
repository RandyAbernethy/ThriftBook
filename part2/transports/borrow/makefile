TARGET = borrow
SRC = borrow.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11

all: borrow

borrow: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) $(TARGET)
