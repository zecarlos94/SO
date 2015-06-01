
all: servidor cliente

servidor: servidor3.c myexec.c packets.c contabilidade2.c pidStatReader.c
	gcc servidor3.c myexec.c packets.c contabilidade2.c pidStatReader.c -o server 

cliente: cliente3.c packets.c
	gcc cliente3.c packets.c -o client

clean:
	rm -f server client
