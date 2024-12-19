C = gcc
CFLAGS = -Wall -Wextra
all: main
main: main.o filework.o
        $(CC) $(CFLAGS) -o main main.o filework.o
main.o: main.c filework.h
        $(CC) $(CFLAGS) -c main.c
filework.o: filework.c filework.h
        $(CC) $(CFLAGS) -c filework.c
clean:
        rm -f *.o main videos.txt

