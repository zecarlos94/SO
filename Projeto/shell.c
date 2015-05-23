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
  int i;  
  char* nome,password;
  char* getnome,getpassword;
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  if(scanf("%s", &nome));
  printf ("ESCREVA A SUA PASSWORD\n");
  if(scanf("%s", &password));
  /*Para cada i corresponde a informação nos arrays do mesmo utilizador*/
  if(ga->size==0) puts("\nNÃO EXISTEM UTILIZADORES\n");
  for(i=0;i<ga->size;i++){
    Utilizadores aux=ga->Elems[i];
  	getnome=aux->nome;
  	getpassword=aux->password;
  	printf("%s\n", getnome);
	  printf("%s\n", getpassword);  	
    if(strcmp(getnome,nome) && strcmp(getpassword,password)){
      printf("BEM VINDO %s !!!\n", getnome);
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
  char* nm,pass;
  int saldo=START;
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  if(scanf("%s", &nm));
  printf ("ESCREVA A SUA PASSWORD\n");
  if(scanf("%s", &pass));
  Utilizadores u = (Utilizadores) malloc(sizeof(struct user));
  u->saldo = saldo;
  u->nome = malloc(100*sizeof(char));
  u->password = malloc(100*sizeof(char));
  u->nome = nm;
  u->password = pass;
  insertGrowingArray(ga,u); 
  printf("%d\n", ga->size);
}


int main(){
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