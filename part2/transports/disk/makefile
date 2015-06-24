TARGET = file_trans
SRC = file_trans.cpp

CC = g++
LIBS = -lthrift
CFLAGS = -Wall -std=c++11

all: file_trans

file_trans: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)
	
clean:
	$(RM) $(TARGET)
	$(RM) data
