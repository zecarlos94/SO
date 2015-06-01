
all: servidor cliente

servidor: servidor.c myexec.c packets.c contabilidade.c 
	gcc servidor.c myexec.c packets.c contabilidade.c -o server 

cliente: cliente.c packets.c
	gcc cliente.c packets.c -o client

clean:
	rm -f server client
