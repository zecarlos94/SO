#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

ssize_t readln(int file, char *buffer, size_t nbyte){ 
  int i = 0; int n; 
  do{ 
    n = read (file, &buffer[i], 1); i++; 
  }while ( n>0 && (buffer[i-1] != '\n') && i<nbyte); 
  buffer[i-1]='\0'; 
  if (n>0) return i;
    else return -1; 
}

int main()
{
   int contabilidade_servidor;
   char *contserv = "/tmp/contserv";
   int servidor_contabilidade;
   char *servcont = "/tmp/servcont";
   char str[128];
   mkfifo(contserv, 0666);
   mkfifo(servcont, 0666);
   do{
   printf("Mensagem que pretende enviar: \n");
   readln(0,str,128);
   contabilidade_servidor = open(contserv, O_WRONLY);
   servidor_contabilidade = open(servcont, O_RDONLY);
   write(contabilidade_servidor, str, sizeof(str));
   perror("Envio para a contabilidade: "); 
   read(servidor_contabilidade,str,sizeof(str));
   perror("Leitura da contabilidade: "); 
   printf("\n...resultado da contabilidade: %s\n",str);
   }while(strcmp(str,"terminar")!=0);
   close(contabilidade_servidor);
   close(servidor_contabilidade);
   unlink(contserv);
   unlink(servcont);
   return 0;
}
