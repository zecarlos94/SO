
all: servidor cliente

servidor: servidor.c myexec.c
	gcc servidor.c myexec.c -o server 

cliente: cliente.c
	gcc cliente.c -o client

clean:
	rm -f server client
