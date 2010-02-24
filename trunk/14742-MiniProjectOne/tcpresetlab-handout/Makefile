CC = gcc
CFLAGS = -O -Wall

all: client server reset

client: client.c
	$(CC) $(CFLAGS) -o client client.c

server: server.c
	$(CC) $(CFLAGS) -o server server.c

reset: reset.c
	$(CC) $(CFLAGS) -o reset reset.c -lnet


# Forces a recompile. Used by the driver program. 
explicit: 
	$(CC) $(CFLAGS) -o client client.c
	$(CC) $(CFLAGS) -o server server.c
	$(CC) $(CFLAGS) -o reset reset.c -lnet

clean:
	rm -f *.o client server reset 

