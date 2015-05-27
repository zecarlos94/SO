CFLAGS= -ansi -Wall -pedantic -O2 
OBJS = servidor.o
OBJ = cliente.o

all: server client

server: $(OBJS)
	gcc $(OBJS) -o server

client: $(OBJ)
	gcc $(OBJS) -o client

servidor: servidor.c
	gcc $(CFLAGS) -c servidor.c  

cliente: cliente.c
	gcc $(CFLAGS) -c cliente.c

clean:
	rm -f *.o
