.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=query.exe
OBJS=test_main.o StringUtil.o TextQuery.o
STAND= -std=c++0x
LINKS=-lmuduo_base -lpthread
$(BIN):$(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ $(LINKS)
%.o:%.cpp
		$(CC) $(CFLAGS) -c $< -o $@ $(STAND)
clean:
		rm -f *.o $(BIN)
