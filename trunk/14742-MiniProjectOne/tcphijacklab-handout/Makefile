CC = gcc
CFLAGS = -O -Wall

all: client hijack

client: client.c
	$(CC) $(CFLAGS) -o client client.c

hijack: hijack.c
	$(CC) $(CFLAGS) -o hijack hijack.c -lnet -lpcap


# Forces a recompile. Used by the driver program. 
explicit: 
	$(CC) $(CFLAGS) -o client client.c
	$(CC) $(CFLAGS) -o hijack hijack.c -lnet -lpcap

clean:
	rm -f *.o client hijack 

