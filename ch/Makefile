.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=ChineseFrequency.exe
OBJS=test_main.o ChineseFrequency.o
STAND= -std=c++0x
LINKS=-lmuduo_base -lpthread

$(BIN):$(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ $(LINKS)
%.o:%.cpp
		$(CC) $(CFLAGS) -c $< -o $@ $(STAND)
clean:
		rm -f *.o $(BIN)
