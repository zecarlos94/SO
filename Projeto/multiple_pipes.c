#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <stdio.h>

char** tokenBars(char* comando)
{
    int i=0;
    char** resultado=malloc(15*sizeof(char*)); // 15 comandos
    char *t;
     
    t = strtok(comando, "|");

    while (t != NULL) {
        resultado[i]=t;
        i++;
	t = strtok(NULL,"|");
    }
    resultado[i] = NULL;
    
    return resultado;
}

char*** tokenSpaces(char** v )
{
    char*** res = malloc(15*sizeof(char**));// 15 comandos
    int i,j;
    for(i = 0;i < 15;i++) // Cada comando tem Maximo 15 argumentos
	res[i] = malloc(15*sizeof(char*)); 

    i = 0;
    while( v[i] != NULL)
    {
	char* t = strtok(v[i]," ");
	j = 0;
	while(t)
	{
	  res[i][j] = t;
          j++;
	  t = strtok(NULL," ");
	}
	res[i][j] = NULL;
	i++;
    }
    res[i] = NULL;
    return res;
}

int loop_pipe (char*** cmd);

void runPipe(char* comando){ 
    char** div1=tokenBars(comando); 
    char*** final = tokenSpaces(div1); 
    loop_pipe(final);
}

int main(){
    char exemplo[50] = "ls -l | wc ";
    runPipe(exemplo);  
    return 0;
}

int loop_pipe (char*** cmd){

  int fd_in;
  int pd[2]; //indice 0 é leitura; indice 1 é escrita (simula um open no lado da escrita e no lado da leitura)


  while(*cmd)
   {	 
    
    pipe(pd);
    if(fork()==0){		
                dup2(fd_in,0); //muda o input para o anterior
		
		if(*(cmd +1))	dup2(pd[1],1);
		
		close(pd[0]);
		execvp(*cmd[0],*cmd);
                _exit(0);
        }
   else {
		wait(NULL);
		close(pd[1]);
		fd_in = pd[0]; //guarda o input para o proximo
        }
     cmd++;   
    }
return 0;
}
