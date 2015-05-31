#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "packets.h"

#define SIZE 1000

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
   int cliente_servidor,i;
   char *cs = "/tmp/server";
   int servidor_cliente;
   char sc[20] = "/tmp/";
   char str[SIZE];
   char mem[SIZE];
   
   char pidS[20];
   sprintf(pidS,"%d",getpid());
   strcat(sc,pidS);// acrescenta o numero do pid a /tmp/

	printf("%s\n",sc);

   memset(str, 0, sizeof(str));
   memset(mem, 0, sizeof(mem));
   
   printf("Memória que deseja alocar: \n");
   readln(0,mem,SIZE);

   Packet packetM = initPacket(getpid(),atoi(mem),NULL);

   cliente_servidor = open(cs, O_WRONLY);

   writePacket(cliente_servidor,packetM);

   printf("Introduza os comandos que pretender: \n");
   puts("Escreva 'terminar' para sair");
   memset(str, 0, sizeof(str));



   while(1)
	{
   	  readln(0,str,SIZE);

   	  if(strcmp(str,"terminar")==0) break;	



  	  Packet packetC = initPacket(getpid(),sizeof(str),str);
	  
	  writePacket(cliente_servidor,packetC);

   	  servidor_cliente = open(sc, O_RDONLY);
	  

  	  
   	  printf("\n...resultado do Servidor...\n");
	  
	  read(servidor_cliente,str,sizeof(str));
	  perror("Read:");   	  

	
   	  close(servidor_cliente);
	  memset(str, 0, sizeof(str));
   	}
   
   
   close(cliente_servidor);
   
   return 0;

}
