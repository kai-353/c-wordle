CC = gcc

CompileParms = -c -Wall -Wextra -std=c99

OBJS = wordle.o string.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o wordle

clean:
	rm -f *.o wordle

string.o: string.c string.h
	$(CC) $(CompileParms) string.c -o string.o

wordle.o: wordle.c string.h
	$(CC) $(CompileParms) wordle.c -o wordle.o
