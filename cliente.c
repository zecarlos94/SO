#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
   int cliente_servidor;
   char *cs = "/tmp/cs";
   int servidor_cliente;
   char *sc = "/tmp/sc";
   char str[128];
   do{
   printf("Mensagem que pretende enviar: \n");
   /*scanf("%s", str); impede a leitura de comandos, por exemplo,ls -la separa em duas leituras resultando em 2 comandos diferentes*/
   readln(0,str,128);
   cliente_servidor = open(cs, O_WRONLY);
   servidor_cliente = open(sc, O_RDONLY);
   write(cliente_servidor, str, sizeof(str));
   perror("Envio para o Servidor: "); 
   read(servidor_cliente,str,sizeof(str));
   perror("Leitura do Servidor: "); 
   printf("\n...resultado do Servidor: %s\n",str);
   }while(strcmp(str,"terminar")!=0);
   close(cliente_servidor);
   close(servidor_cliente);
   return 0;
}