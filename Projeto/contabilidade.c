#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "growingArray.c"

int actualizaSaldo(GrowingArray ga, int pid){
   int res=-1;
   int i,saldo_actual,pid_actual;
   for(i=0;i<ga->size;i++){
      Clientes aux=ga->Elems[i];
      saldo_actual=aux->saldo;
      pid_actual=aux->pid_number;
      if(pid_actual==pid){
         aux->saldo--;
      }
   }
   return res;
}

int main()
{
   int res;
   GrowingArray ga = initGrowingArray(10000);
   int contabilidade_servidor;
   char *contserv = "/tmp/contserv";
   int servidor_contabilidade;
   char *servcont = "/tmp/servcont";
   char buffer[128];
   contabilidade_servidor = open(contserv, O_RDONLY);
   servidor_contabilidade = open(servcont, O_WRONLY);
   printf("Servidor Ligado.\n");
   while (1) {
    read(contabilidade_servidor, buffer, 128);
    res=actualizaSaldo(ga,getpid());
    if (strcmp("exit",buffer)==0) {
        printf("Servidor Desligado.\n");
        break;
    }else if (strcmp("",buffer)!=0) {
        printf("Recebido: %s\n", buffer);
        printf("A enviar de volta a mensagem ao Servidor...\n");
        write(servidor_contabilidade,buffer,128);
    }
    memset(buffer, 0, sizeof(buffer));
   }
   close(contabilidade_servidor);
   close(servidor_contabilidade);
   return 0;
}
