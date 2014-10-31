.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=wordFrequency.exe
OBJS=test_main.o StringUtil.o WordFrequency.o
STAND= -std=c++0x
LINKS=-lmuduo_base -lpthread
$(BIN):$(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ $(LINKS)
%.o:%.cpp
		$(CC) $(CFLAGS) -c $< -o $@ $(STAND)
clean:
		rm -f *.o $(BIN)
