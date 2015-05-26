#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "readln.h"

int cloudShell(char* cmd){
	int n=0;char* a[1000];
	a[n]=strtok(cmd, " ");
	while(a[n]) a[++n]=strtok(NULL, " ");
	
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

void executa(){
	char buf[1000];
	while(1){
		write(1,"cloudShell $ ",14);
		readln(0,buf,1000);
		cloudShell(buf);
        if(buf[0]=='S' && buf[1]=='\0') break;
	}
}

/*
$ xeyes & -> permite executar comandos em background

O cliente.c e um ficheiro com o pipe criado pela cloudshell que o abre e envia sinais por ele
Na cloudshell.c tem a shell e cria um novo pipe com nome mkfifo("",0666)

criar ficheiro com extensão .sh e fazer chmod 0777 nomeficheiro.sh
e depois basta fazer o ./nomeficheiro.sh e ele executa tudo =>>script em bash

unzip faz o unzip da pasta .zip
*/






