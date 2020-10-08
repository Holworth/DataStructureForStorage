OBJS = skiplist.o

CC 		= g++
TARGET 	= main
CFLAGS 	= -Wall -g -O2
STD    	= -std=c++11
CLIB	= -pthread

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(STD) $(CLIB)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) $(CLIB)

default:
	make $(TARGET)

clean:
	rm -rf *.o $(TARGET) 
