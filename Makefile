CC=gcc
CFLAGS=-Wall-Wextra -std=c99

build:
	gcc my_octave.c -o my_octave
clean:
	rm -f my_octave
