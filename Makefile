CC = gcc

CompileParms = -c -Wall -Wextra -std=c99

OBJS = wordle.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o wordle

clean:
	rm -f *.o wordle

wordle.o: wordle.c
	$(CC) $(CompileParms) wordle.c -o wordle.o
