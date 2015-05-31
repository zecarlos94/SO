#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "packets.h"

#define SIZE 10000

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
   char BUFF1[SIZE];
   char BUFF2[SIZE];
   
   char pidS[20];
   sprintf(pidS,"%d",getpid());
   strcat(sc,pidS);// acrescenta o numero do pid a /tmp/

	printf("%s\n",sc);

   memset(BUFF1, 0, SIZE);
   memset(BUFF2, 0, SIZE);
   
   printf("Memória que deseja alocar: \n");
   readln(0,BUFF1,SIZE);

   Packet packetM = initPacket(getpid(),atoi(BUFF1),NULL);

   cliente_servidor = open(cs, O_WRONLY);

   writePacket(cliente_servidor,packetM);

   
   memset(BUFF1, 0, SIZE );



   while(1)
	{
   	  
   	  printf("Introduza os comandos que pretender: \n");
  	  puts("Escreva 'terminar' para sair");
	 
           readln(0,BUFF1,SIZE);

   	  if(strcmp(BUFF1,"terminar")==0) break;	

	  if (!(strcmp(BUFF1,"")==0 || strcmp(BUFF1,"\n") == 0))

	  {
  	  Packet packetC = initPacket(getpid(),sizeof(BUFF1),BUFF1);
	  
	  
	  
	  writePacket(cliente_servidor,packetC);
	  perror("Write:");


	  servidor_cliente = open(sc, O_RDONLY);
	  perror("Open read channel");   	 

 
   	  printf("\n...resultado do Servidor...\n");
	  
	  
	  read(servidor_cliente,BUFF2,SIZE);
	  
	  perror("Read:");   	  

	  
	  printf("%s\n",BUFF2);

	  }

	  memset(BUFF1, 0, SIZE );
	  memset(BUFF2, 0, SIZE );
   	  
	}
   
   
   close(servidor_cliente);
   close(cliente_servidor);
   
   return 0;

}
