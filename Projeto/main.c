#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "growingArray.h"
#include "cloudShell.h"

#define START 1000

void menu() {
        printf ("\n\n--------------------------------MENU----------------------------------------\n\n");
        printf ("1 - LOGIN\n");
        printf ("2 - REGISTAR\n");
        printf ("----------------------------------------------------------------------------\n\n");
  }

void login(GrowingArray ga){  
  int i;
  char nm[100],pass[100];
  /*Para cada i corresponde a informação nos arrays do mesmo utilizador*/
  if(ga->size==0) {puts("\nNÃO EXISTEM UTILIZADORES\n");exit(1);}
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  scanf("%s",nm);
  printf ("ESCREVA A SUA PASSWORD\n");
  scanf("%s",pass);
  for(i=0; i<ga->size; i++)
  {
    Utilizador aux=ga->Elems[i];
    if(strcmp(aux->nome,nm)==0 && strcmp(aux->password,pass)==0 )
    {
      printf("BEM VINDO %s !!!\n", aux->nome);
       /*onde vai executar a cloudShell*/
      executa();
      printf("ADEUS %s\n", aux->nome);
    }
  }
}


void registar(GrowingArray ga){
  char nm[100],pass[100];
  int saldo=START;
  printf ("ESCREVA O SEU NOME DE UTILIZADOR\n");
  scanf("%s",nm);
  printf ("ESCREVA A SUA PASSWORD\n");
  scanf("%s",pass);
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