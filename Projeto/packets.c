#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_BUFFER 1024

typedef struct packet{
	int pid;
	int length;
	char* data;
}Packet;


Packet initPacket(int pid,int length,char* data)
{
	Packet* p = malloc(sizeof(Packet));
	p->pid = pid;
	p->data = data;
	p->length = length;
	return (*p);	
}

// Usado para enviar dados de memoria apenas
int isPacketInt(Packet p)
{
	return (p.pid>0 && p.length > 0 && p.data == NULL);
}

int isPacketData(Packet p)
{
	return (p.pid>0 && p.length > 0 && p.data != NULL);
}

int isValidPacket(Packet p)
{
	return (p.pid > 0 && p.length > 0);
}

Packet aggregatePacket(char* info);

char* disaggregatePacket(Packet p);

int writePacket(int fd,Packet p)
{
	char* data = disaggregatePacket(p);

	return write(fd,data,strlen(data));
}

int readPacket(int fd,Packet* p)
{
	char data[MAX_BUFFER];
	int r;
	r = read(fd,data,MAX_BUFFER);
	if (r > 0) (*p) = aggregatePacket(data);
	return r; 
}

Packet aggregatePacket(char* info)
{
	char* t,*data;
	Packet p;
	int pid,length;
	t = strtok(info,";");
	pid = atoi(t);
	t = strtok(NULL,";");
	length = atoi(t);
	t = strtok(NULL,";");
	data = t;
	
	p = initPacket(pid,length,data);
	return p;
}

char* concat(char *s1, char *s2);

char* disaggregatePacket(Packet p)
{
	char pid[10];
	char length[10];
	char *result,*part1;
	
	sprintf(pid,"%d",p.pid);
	sprintf(length,"%d",p.length);

	part1 = concat(pid,length);
	result = concat(part1,p.data);
	
	return result;
}

// Adiciona um ; para separar a informação
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+2);//+2 para /0 e ;
    strcpy(result, s1);
    strcat(result,";");
    strcat(result, s2);
    return result;
}


int main()
{
	Packet p = initPacket(1000,20,"AI FUNCIONA");
	char* data = disaggregatePacket(p);
	printf("Informação do pacote =%s\n",data);
	p = aggregatePacket(data);
	printf("Pid = %d, length = %d, data = %s\n",p.pid,p.length,p.data);	
}
