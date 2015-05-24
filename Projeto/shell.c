#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "growingArray.c"

#define START 1000

ssize_t readln(int file, char *buf, size_t nbyte){ 
	int i = 0; int n; 
	do{ 
		n = read (file, &buf[i], 1); i++; 
	}while ( n>0 && (buf[i-1] != '\n') && i<nbyte); 
	buf[i-1]=0; 
	if (n>0) return i;
    else return -1; 
}

int cloudShell(char* cmd){
	int n=0;char* a[1000];
	a[n]=strtok(cmd, " ");
	while(a[n]) a[++n]=strtok(NULL, " ");
	//strtok(0," \n");
	
	if(!fork()){
		if(!strcmp(a[0],"cd")){chdir(a[1]);}
		else{
		execvp(a[0],a);
		exit(1);
		}
	}
	else{
		wait(NULL);
	}
	return 0;	
}

void menu() {
        printf ("\n\n--------------------------------MENU----------------------------------------\n\n");
        printf ("1 - LOGIN\n");
        printf ("2 - REGISTAR\n");
        printf ("----------------------------------------------------------------------------\n\n");
  }

void login(GrowingArray ga){  
  int corta,i;
  char nm[100],pass[100];
  /*Para cada i corresponde a informação nos arrays do mesmo utilizador*/
  if(ga->size==0) {puts("\nNÃO EXISTEM UTILIZADORES\n");exit(1);}
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  fgets(nm,100,stdin);
  corta=strlen(nm)-1;
  if(nm[corta]=='\n') nm[corta]=='\0';
  printf ("ESCREVA A SUA PASSWORD\n");
  fgets(pass,100,stdin);
  corta=strlen(pass)-1;
  if(pass[corta]=='\n') pass[corta]=='\0';
  for(i=0; i<ga->size; i++){
    Utilizador aux=ga->Elems[i];
    if(strcmp(aux->nome,nm) && strcmp(aux->password,pass)) {
      printf("BEM VINDO %s !!!\n", aux->nome);
       /*onde vai executar a cloudShell*/
      char* cmd;
      char buf[1000];
      while(1){
         write(1,"cloudShell $ ",14);
         readln(0,buf,1000);
         cloudShell(buf);
         if(buf[0]=='S' && buf[1]=='\0') break;
      }
    }
  }
}


void registar(GrowingArray ga){
  char nm[100],pass[100];
  int corta;
  int saldo=START;
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  fgets(nm,100,stdin);
  corta=strlen(nm)-1;
  if(nm[corta]=='\n') nm[corta]=='\0';
  printf ("ESCREVA A SUA PASSWORD\n");
  fgets(pass,100,stdin);
  corta=strlen(pass)-1;
  if(pass[corta]=='\n') pass[corta]=='\0';
  Utilizador cp1 = malloc(sizeof(struct user));
  cp1->nome=nm;
  cp1->password=pass;
  cp1->saldo=START;
  insertGrowingArray(ga,cp1);
}




int main()
{
  int opcao;
  GrowingArray ga = initGrowingArray(10000);
  while(1) {
    char c;
    menu();
    printf ("\nESCOLHA UMA OPÇÃO: ");
    if(scanf("%d", &opcao) && opcao > 0) {
      switch(opcao) {
        case 1:login(ga);break;      
        case 2:registar(ga);break;  
        default: puts("Opção Inválida!!!\n");return 1;               
      } 
    }
    puts("PARA SAIR 'N', PARA CONTINUAR 'S'");
    if(scanf(" %c",&c) && (c=='n' || c == 'N')) break; 
  }
  return 0;
}