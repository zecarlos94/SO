#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

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

void cloudShell(char* cmd){
  int n=0;char* a[1000];
  a[n]=strtok(cmd, " ");
  while(a[n]) a[++n]=strtok(NULL, " ");
  start=clock();
  signal(SIGCHLD, sigchld_handler);
    fpid = fork();
  if (fpid == 0) 
  {  /*Filho*/
      printf("%d\n", getpid());
      if(!strcmp(a[0],"cd")){chdir(a[1]);}
    else
    {
      execvp(a[0],a);
      _exit(4);
    }
    } 
    else {          /*Pai*/
      sleep(5);
    stop=clock();
      printf("Pai acordou , %d\n", fpid);
      printf("%.10f segundos\n", (double)((stop-start)/CLOCKS_PER_SEC));
      sleep(1);
    }
} 

int main()
{
   int cliente_servidor;
   char *cs = "/tmp/cs";
   int servidor_cliente;
   char *sc = "/tmp/sc";
   char buffer[128];
   mkfifo(cs, 0666);
   mkfifo(sc, 0666);
   cliente_servidor = open(cs, O_RDONLY);
   servidor_cliente = open(sc, O_WRONLY);
   printf("Servidor Ligado.\n");
   while (1) {
    read(cliente_servidor, buffer, 128);
    if (strcmp("exit",buffer)==0) {
        printf("Servidor Desligado.\n");
        break;
    }else if (strcmp("",buffer)!=0) {
        printf("Recebido: %s\n", buffer);
        cloudShell(buffer);
        printf("A enviar de volta a mensagem ao cliente...\n");
        write(servidor_cliente,buffer,128);
    }
    memset(buffer, 0, sizeof(buffer));
   }
   close(cliente_servidor);
   close(servidor_cliente);
   unlink(cs);
   unlink(sc);
   return 0;
}