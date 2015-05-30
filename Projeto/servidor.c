#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#include "myexec.h"

#define SIZE 1000

typedef void (*sighandler_t)(int);

clock_t start, stop;
int fpid, status;

void sigchld_handler (int sig) {
  printf("Filho morreu\n");
  waitpid(fpid, &status, 0);
}

void sigalrm_handler (int sig) {
  printf("Está aí alguém?\n");
}

char* cloudShell(char* cmd){
  int n=0;char* a[SIZE];
  
  start=clock();
  char* resultado = malloc(1024); // mensagem
	
  int pd[2];
  pipe(pd);
 
  fpid = fork();
  if (fpid == 0) 
  {  /*Filho*/
      printf("%d\n", getpid());
      dup2(pd[1],1);
      close(pd[1]);
      myexec(cmd);
      _exit(4);
 //   }
  } 
    else {          /*Pai*/
      close(pd[1]);
/* Coloca o output do comando em resultado */
      while (read(pd[0], resultado , 1024));
      close(pd[0]);
      stop=clock();
      printf("Pai acordou , %d\n", fpid);
      printf("%.10f segundos\n", (double)((stop-start)/CLOCKS_PER_SEC));
  
      return resultado;  
  }
} 

int main()
{
   int cliente_servidor;
   char *cs = "/tmp/cs";
   int servidor_cliente;
   char *sc = "/tmp/sc";
   char buffer[SIZE];
   char* resultado;
   mkfifo(cs, 0666);
   mkfifo(sc, 0666);
   cliente_servidor = open(cs, O_RDONLY);
   servidor_cliente = open(sc, O_WRONLY);
   printf("Servidor Ligado.\n");
   memset(buffer, 0, sizeof(buffer));
   while(1){
      memset(buffer, 0, sizeof(buffer));
      read(cliente_servidor, buffer, SIZE);
      //int memoria = atoi(buffer) * 1024;//bytes , 1char = 1byte
      if (strcmp("",buffer)!=0) {
        int memoria;
        read(servidor_cliente, &memoria, sizeof(int));
        printf("Memoria pedida %d bytes\n",memoria);
        printf("Recebido: %s\n", buffer);
        resultado = cloudShell(buffer);
        printf("A enviar de volta a mensagem ao cliente...\n");
        write(servidor_cliente, resultado , 1024);
      }
      memset(buffer, 0, sizeof(buffer));
   }
   close(cliente_servidor);
   close(servidor_cliente);
   unlink(cs);
   unlink(sc);
   return 0;
}

