#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "so.c"

#define START 1000

Vector vector;/*Variável global*/
  
int main(){
  int opcao;
  vector_init(&vector);/*vector.size==0*/
  
  while(1) {
    char c;
    menu();
          printf ("\nESCOLHA UMA OPÇÃO: ");
    if(scanf("%d", &opcao) && opcao > 0) {
      switch(opcao) {
        case 1:login(vector);break;      
        case 2:registar(vector);break;  
        default: puts("Opção Inválida!!!\n");return 1;               
      } 
    }
    puts("PARA SAIR 'N', PARA CONTINUAR 'S'");
    if(scanf(" %c",&c) && (c=='n' || c == 'N')) break; 
  }
  vector_free(&vector);
  return 0;
}

void menu () {
        printf ("\n\n--------------------------------MENU----------------------------------------\n\n");
        printf ("1 - LOGIN\n");
        printf ("2 - REGISTAR\n");
        printf ("----------------------------------------------------------------------------\n\n");
  }

void login(Vector vector){
  int i;  
  char* nome,password;
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  if(scanf("%s", &nome));
  printf ("ESCREVA A SUA PASSWORD\n");
  if(scanf("%s", &password));
  /*Para cada i corresponde a informação nos arrays do mesmo utilizador*/
  for(i=0;i<tamanho;i++){/*Dá segmentation fault*/
    if((strcmp(vector_getNomes(&vector,i),nome)) && (strcmp(vector_getPasswords(&vector,i),password)) ){
      printf("BEM VINDO %s !!!\n", nome);
      /*onde vai executar a cloudShell*/
      char* cmd;
      char buf[1000];
      char c;
      while(1){
        write(1,"CloudShell $ ",13);
        readln(0,buf,1000);
        if(buf[0]=='S'&& buf[1]=='\0') break;
        cloudShell(buf);
      }

    }
  }
}

void registar(Vector vector){
  char* nome,password;
  int saldo=START;
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  if(scanf("%s", &nome))
  printf ("ESCREVA A SUA PASSWORD\n");
  if(scanf("%s", &password))
  vector_append(&vector, nome, password, saldo);
  printf("%d\n", tamanho);
}


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