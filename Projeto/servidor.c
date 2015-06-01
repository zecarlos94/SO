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
#include "packets.h"
#include "contabilidade.h"

#define SIZE 10000

clock_t start, stop;

char *cs = "/tmp/server";

int cliente_servidor;

Contabilidade cont;

void sigint_handler (int sig) {

   int j;
    
   printf("\n\nUnlinking pipes before shutdown\n\n");
   
   for(j=0;j < cont->size;j++)
	unlink(cont->clientes[j]->pipe);

   close(cliente_servidor);
   unlink(cs);

   exit(1);    
}

char* cloudShell(char* cmd);

int main()
{
   cont = initContabilidade(10);

   int servidor_cliente,i;

   signal(SIGINT,sigint_handler);
 
   mkfifo(cs, 0666); // De leitura
   
   cliente_servidor = open(cs, O_RDONLY);

   printf("Servidor Ligado.\n");
   

   Packet* packets = malloc(10*sizeof(Packet)); // 10 pacotes MAX

   while(1){

      readPacket(cliente_servidor,packets);      
 
     for(i = 0 ; isValidPacket(packets[i]) ; i++){
      
      int pid = packets[i].pid;

      start=clock();

	/* Se o pacote foi utilizado para mandar apenas um int,
	significa que o utilizador comprou memória, logo cria-se uma conta */
      if ( isPacketInt(packets[i]) ) 
      {
         
   /* Cria pipe do utilizador */
        char sc[20] = "/tmp/";
        char pidS[20];  
        sprintf(pidS,"%d",pid);     
        strcat(sc,pidS);// acrescenta o numero do pid a /tmp/

	int memoria_comprada = packets[0].length * 1024;
        printf("Memoria comprada %d bytes\n",memoria_comprada);
       	criaConta(cont,pid,memoria_comprada,sc); // adicionar char* sc
        mkfifo(sc, 0666);// De escrita
      } 
	
 
     else if ( isPacketData(packets[i])) 
      {
	Cliente cliente = dadosCliente(cont,pid);
	char* sc = cliente->pipe; 
	
        servidor_cliente = open(sc, O_WRONLY);
        perror("Open:");
	

	// O limite do cliente excedeu 
	if(cliente->memoria_comprada < cliente->memoria_utilizada)
	{
	
		printf("Cliente sem memoria\n");
		kill(pid,SIGUSR1);
	}
	else if (cliente->saldo <= 0)
	{
		printf("Cliente sem saldo\n");
		kill(pid,SIGUSR2);
	}
	else{
   		char* resultado;
	
		int memoria=0;

		printPacket(packets[i]);
	
       		resultado = cloudShell( packets[i].data );
        
        	write(servidor_cliente, resultado , SIZE);
   	
		perror("Write:");

		memoria = (int)strlen(resultado);

		cliente->memoria_utilizada+= memoria;      	

		printf("Memoria descontada:%dBytes\n",memoria);


		free(resultado);

		cliente->saldo--;   	
     
	} 
      }
	// Final do tratamento do pacote

      	stop=clock();
      
	printf("Duração:%.10f segundos\n", (double)((stop-start)/CLOCKS_PER_SEC));
      
	//final do tratamento do pacote
	printf("Cliente: %d atendido\n\n",pid);
     }
   // Final do tratamento de todos os pacotes, read mais
      cleanPackets(packets,10);

   }

   return 0;
}

char* cloudShell(char* cmd){
  int n=0;
  
  char* resultado = malloc(SIZE*sizeof(char)); // mensagem

  memset(resultado,0,SIZE);
	
  int pd[2],fpid;
  pipe(pd);
 
  fpid = fork();
  if (fpid == 0) 
  {  /*Filho*/
      dup2(pd[1],1);
      close(pd[1]);
      myexec(cmd);
      _exit(4);
  } 
    else {          /*Pai*/
      close(pd[1]);
/* Coloca o output do comando em resultado */
      while (read(pd[0], resultado , SIZE));
      close(pd[0]);
      
      return resultado;  
  }
}
