#Makefile
#ZKR Clock

all: main

main: main.c clock.c
	clang main.c clock.c -o clock -lasound -lm `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -f *.o clock
