CC = clang
CFLAGS = -g -Wall

all: main run

main: main.c
	@$(CC) $(CFLAGS) -o main main.c

run: main
	@./main

clean:
	rm -f main