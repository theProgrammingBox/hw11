CC = g++
FLAGS = -std=c++14 -Wall -g
OBJS = hw11.o
FILES = hw11.cpp

all: hw11

hw11: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o hw11

hw11.o: hw11.cpp
	$(CC) $(FLAGS) -c hw11.cpp

tar:
	tar -cf hw11.tar hw11.scr Makefile $(FILES)

clean:
	rm *.o *.tar *.scr hw11

sudoClean:
	rm *.o *.scr hw11