
all: servidor cliente

servidor: servidor.c myexec.c packets.c contabilidade2.c
	gcc servidor2.c myexec.c packets.c contabilidade2.c -o server 

cliente: cliente.c packets.c
	gcc cliente2.c packets.c -o client

clean:
	rm -f server client
