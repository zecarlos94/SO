#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/signal.h>

#define MAX_LINE 200

typedef struct pidInfo{
	int pid;
	double cpu;//%
}PidInfo;

typedef struct pidData{
	PidInfo* data;
	int size; 
}pidData;

typedef pidData* PidData;

int existe(int* pids,int N,int checkPid);

void setPoint(char* s)
{
	int N = strlen(s);
	int i;
	for(i=0;i<N;i++)
		if(s[i] == ',')
			{
				s[i] = '.';break;
			}
}

int readln(char* linha,int fd){
	int i;
	char c;
	int eof = 1;
	for(i=0; (eof = read(fd,&c,1)) && c!= '\n' && i-1 < MAX_LINE;i++)
		linha[i] = c;
	linha[i] = '\0';
	return eof;
}

PidData collectCPU( int* pids, int N)
{
	PidData r = malloc(sizeof(struct pidData)); 
	int i;
	r->data = malloc(N*sizeof(struct pidInfo));
	r->size = 0;

	for(i = 0;i < N; i++)
	{
	  r->data[i].pid = -1;
	  r->data[i].cpu = -1;
	}
	
	char linha[MAX_LINE];
	int pd[2];
	pipe(pd);

	if(fork()==0)
		{
			close(pd[0]);
			dup2(pd[1],1);
			execlp("pidstat","pidstat",NULL);
			close(pd[1]);
		}
	close(pd[1]);

	readln(linha,pd[0]);	// deita a primeira linha fora
	
	for(i = 0; readln(linha,pd[0]);)
	{
		linha[strlen(linha)-1] = '\0'; //apagar
		char* t = strtok(linha," ");
		int x = 0;
		int encontrou = 0;
		while(t!=NULL)
		{
		  if( x == 2) // PID
			{
			  int checkPid = atoi(t);
			  if( existe(pids,N,checkPid) ) 
				{
				  r->data[i].pid = checkPid;
				  r->size++;
				  encontrou = 1;
				}
			}
		  if( x == 6 && encontrou) // % CPU
			  {
				setPoint(t);//passa a virgula a ponto
				r->data[i].cpu = (double)atof(t);
			  }
		  x++;
		  t = strtok(NULL," ");
		}
		if ( encontrou ) i++;
	}
	return r;
}

// recebe os pids que quer analisar
int main(int argc, char* argv[])
{
	int N = argc - 1;
	int i;
	PidData intel;
	int* pids = malloc(N);
	for(i=0 ; i < N ; i++)
		pids[i] = atoi(argv[i+1]);

	intel = collectCPU(pids,N);
	// Print para verificar resultados
	for(i = 0; i < intel->size; i++)
		printf(" O processo:%d usou %f%%cpu\n",intel->data[i].pid,intel->data[i].cpu);
		
	return 0;
}

int existe(int* pids,int N,int checkPid)
{
	int i;
	for(i=0;i<N;i++)
		if(pids[i] == checkPid) return 1;
	return 0;
}
