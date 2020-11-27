CC		= g++
STD 	= -std=c++17
CLIB	= -lm 
TARGET	= main
INCLUDE	= ./
SRC		= ./BTree.cc
TEST	= ./main.cc
CFLAGS	= -Wall -g


all:
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET) \
	$(CLIB)	\
	-I $(INCLUDE)	\
	$(STD)

clean:
	rm -rf *.o $(TARGET)
