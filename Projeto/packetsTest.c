#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>


#include "packets.h"

#define MAX_BUFFER 1024

void printPacket(Packet p)
{
	printf("Pid:%d\nLength:%d\n",p.pid,p.length);
	if(p.data)
		printf("Data:%s\n",p.data);
   	   else puts("Data:NULL");

}


Packet initPacket(int pid,int length,char* data)
{
	Packet* p = malloc(sizeof(Packet));
	p->pid = pid;
	if(data) p->data = data; else p->data = "NULL";
	p->length = length;
	return (*p);	
}

void cleanPackets(Packet* packets,int N)
{
	int i;
	for(i=0;i<N;i++)
		packets[i] = initPacket(-1,-1,NULL);
}

// Usado para enviar dados de memoria apenas
int isPacketInt(Packet p)
{
	return (p.pid>0 && p.length > 0 && strcmp(p.data,"NULL")==0 );
}

int isPacketData(Packet p)
{
	return (p.pid>0 && p.length > 0 && strcmp(p.data,"NULL")!= 0);
}

int isValidPacket(Packet p)
{
	return (p.pid > 0 && p.length > 0 );
}

void aggregatePackets(char* info,Packet* p);

char* disaggregatePacket(Packet p);

int writePacket(int fd,Packet p)
{
	char* data = disaggregatePacket(p);
	
//	printf(" A enviar a seguinte data:%s\n",data);

	return write(fd,data,strlen(data));
}


// Recebe um array de Pacotes
int readPacket(int fd,Packet* p)
{
	char data[MAX_BUFFER];
	int r;
	char* first = malloc(2*sizeof(char));
	r = read(fd,data,MAX_BUFFER);
	/* todos os pacotes enviados começam pelo pid, logo se
	   o primeiro char nao for um inteiro a informação é lixo	*/

	first[0] = data[1];first[1] = '\0';
        if (r > 0 && (atoi(first)!= 0) && (strcmp(data,"")) ) aggregatePackets(data,p);
	return r; 
}

int size(char* info);

void aggregatePackets(char* info,Packet* p)
{
	char* t,*data,*tokenPacotes;
	int Npackets = size(info),i = 0;
//	Packet* p = malloc( Npackets * sizeof(Packet));
	int pid,length;
  
	
	t = strtok(info,"#;");
	
	while(t && i < Npackets)
	{

	  if(i>0) t = strtok(NULL,"#;");
	  pid = atoi(t);
	  
	
	  t = strtok(NULL,";");
	  length = atoi(t);

	
	  t = strtok(NULL,";#");
	  data = t;
	

	  p[i] = initPacket(pid,length,data);
          i++; 
        }
	
  	p[i] = initPacket(-1,-1,NULL);
	
}


char* concat(char *s1, char *s2,char *s3);

char* disaggregatePacket(Packet p)
{
	char pid[10];
	char length[10];
	char *result,*part1;
	
	sprintf(pid,"%d",p.pid);
	sprintf(length,"%d",p.length);
   
	result = concat(pid,length,p.data);

	return result;
}

// Forma a string #"pid";"length";"data"#
char* concat(char *s1, char *s2,char *s3)
{
    char *result = malloc(strlen(s1)+strlen(s2)+strlen(s3)+5);
    strcpy(result, "#");
    strcat(result, s1);
    strcat(result,";");
    strcat(result, s2);
    strcat(result,";");
    strcat(result, s3);
    strcat(result, "#");
    return result;
}

// Devolve o numero de pacotes recebidos
int size(char* info)
{
    int i,count=0;

    for(i = 0; info[i] ; i++)
	if( info[i] == '#' ) count++;
   
    return count/2;
}



/*
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+4);//+2 para /0 e ; + 2 #
    strcpy(result, s1);
    strcat(result,";");
    strcat(result, s2);
    return result;
}
*/


int main()
{
	Packet p = initPacket(200,10,NULL);
	printf("Teste 1\n");
	printPacket(p); 
	printf("Resultados pid = 200, length = 10, data = NULL\n\n");

	printf("Teste 2\n");

	char* c1 = disaggregatePacket(p);
	int t2 = strcmp(c1,"#200;10;NULL#") == 0,i;
	if(t2) puts("Passou o teste 2"); else printf("Falhou Teste 2: %s\n",c1);

	printf("Teste 3\n\n");
	Packet* packets = malloc(5*sizeof(Packet)); 
	char c2[100] = "#200;10;funciona##201;11;funciona#";
	aggregatePackets(c2,packets);
	for(i=0;isValidPacket(packets[i]);i++)
		printPacket(packets[i]);
	return 0;	
}

