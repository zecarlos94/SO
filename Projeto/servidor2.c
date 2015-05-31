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
   int cliente_servidor,i;
   char *cs = "/tmp/server";
   int servidor_cliente;
   char* resultado;

   Contabilidade contabilidade = initContabilidade(10);  
 
   mkfifo(cs, 0666); // De leitura
   
   cliente_servidor = open(cs, O_RDONLY);

   printf("Servidor Ligado.\n");
   

   Packet* packets = malloc(10*sizeof(Packet)); // 10 pacotes MAX

   while(1){
 
      readPacket(cliente_servidor,packets);      
      perror("Read:");
 
      for(i = 0 ; isValidPacket(packets[i]) ; i++){
      
      char sc[20] = "/tmp/";
      int pid = packets[i].pid;
   /* Deduz o nome do pipe do utilizador */
      char pidS[20];  
      sprintf(pidS,"%d",pid);     
      strcat(sc,pidS);// acrescenta o numero do pid a /tmp/


      mkfifo(sc, 0666);// De escrita
	


	printf("%s\n",sc);

	/* Se o pacote foi utilizado para mandar apenas um int,
	significa que o utilizador comprou memória, logo cria-se uma conta */
      if ( isPacketInt(packets[i]) ) 
      {
         int memoria_comprada = packets[0].length * 1024;
         printf("Memoria comprada %d bytes\n",memoria_comprada);
       	 criaConta(contabilidade,pid,memoria_comprada);
      } 
	
 
     else if ( isPacketData(packets[i])) 
      {

	
        servidor_cliente = open(sc, O_WRONLY);
	
	printPacket(packets[i]);
	
	fflush(stdout);


	/* Verificar aqui memoria e saldo do utilizador com funçoes da Contabilidade*/
        resultado = cloudShell( packets[i].data );
        
	
      //  write( 1 , resultado , 1024);
      
        write(servidor_cliente, resultado , 1024);
   	
	perror("Write:");
      

        close(servidor_cliente);
      }
      
      	unlink(sc);

      }
      cleanPackets(packets,10);

   }
   close(cliente_servidor);
   unlink(cs);
   return 0;
}
