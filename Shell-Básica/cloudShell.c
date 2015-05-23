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

int cloudShell(char* cmd){
	int n=0;char* a[1000];
	a[n]=strtok(cmd, " ");
	while(a[n]) a[++n]=strtok(NULL, " ");
	//strtok(0," \n");
	
	if(!fork()){
		if(!strcmp(a[0],"cd")){chdir(a[1]);}
		else{
		execvp(a[0],a);
		exit(1);
		}
	}
	else{
		wait(NULL);
	}
	return 0;	
}

int main(int argc, char* argv[]){
	char* cmd;
	char buf[1000];
	while(1){
		write(1,"Shell $",8);
		readln(0,buf,1000);
		cloudShell(buf);
	}

	return 0;
}

/*
$ xeyes & -> permite executar comandos em background
*/






