CC = gcc
CFLAGS = -O -Wall

explicit: sslattack

sslattack : sslattack.c
	gcc sslattack.c -g -lpcap -lnet -lresolv -o sslattack

clean:
	rm -f *.o sslattack
