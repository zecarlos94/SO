#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


ssize_t readln(int file, char *buf, size_t nbyte){ 
	int i = 0; int n; 
	do{ 
		n = read (file, &buf[i], 1); i++; 
	}while ( n>0 && (buf[i-1] != '\n') && i<nbyte); 
	buf[i-1]=0; 
	if (n>0) return i;
    else return -1; 
}