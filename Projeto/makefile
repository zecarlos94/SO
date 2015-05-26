CFLAGS= -ansi -Wall -pedantic -O2 
OBJS = main.o growingArray.o readln.o cloudShell.o

projeto: $(OBJS)
	gcc $(OBJS) -o projeto
	make clean

growingArray: growingArray.c
	gcc $(CFLAGS) -c growingArray.c


readln: readln.c
	gcc $(CFLAGS) -c readln.c

cloudShell: cloudShell.c
	gcc $(CFLAGS) -c cloudShell.c 


main : main.c growingArray.h cloudShell.h
	gcc $(CFLAGS) -c main.c 


clean:
	rm -f *.o
