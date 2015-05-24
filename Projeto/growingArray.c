#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "growingArray.h"


/*Inicializa o GrowingArray*/
GrowingArray initGrowingArray(int max_size) {
	GrowingArray novo=malloc(sizeof(struct growingarray));
	novo->size=0;
	novo->max_size=max_size;
	novo->Elems = calloc(max_size,sizeof(Utilizador));
	return novo;
}

/*Insere um novo Utilizador no GrowingArray*/
void insertGrowingArray(GrowingArray a, Objeto o) {
	if(a->size==a->max_size) {
		a->max_size*=1.5; 
		a->Elems=realloc(a->Elems,sizeof(void*) *  a->max_size);
	}	
	a->Elems[a->size]=o;
	a->size+=1;
}

/*Ordena a matriz especializada para a query 9*/	
void ordenaArrayAux(int **arrayAux, int length) {
	qSort(arrayAux, 0, length-1);
}

/*Funcao auxiliar da ordenaArrayAux que ordena a matriz usando quickSort*/
void qSort(int **arrayAux, int left, int right) {
	int i=left, j=right, x=arrayAux[(left+right)/2][0], y[2];
	while(i<=j) {
		while(arrayAux[i][0]>x && i<right) {
			i++;
		}
		while(arrayAux[j][0]<x && j>left) {
			j--;
		}
		if(i<=j) {
			y[0]=arrayAux[i][0];
			y[1]=arrayAux[i][1];
			arrayAux[i][0]=arrayAux[j][0];
			arrayAux[i][1]=arrayAux[j][1];
			arrayAux[j][0]=y[0];
			arrayAux[j][1]=y[1];
			i++; j--;
		}
	}
	if(j>left) qSort(arrayAux, left, j);
	if(i<right) qSort(arrayAux, i, right);
}
	
/* FUNCIONAL SEM SCANFS!!!
int main()
{
	int i;
	char* nome="N/A";
	GrowingArray ga = initGrowingArray(10000);
	Utilizador cp1 = malloc(sizeof(struct user));
	Utilizador cp2 = malloc(sizeof(struct user));
	Utilizador cp3 = malloc(sizeof(struct user));
	cp1->nome="SO";
	cp1->password="abc";
	cp1->saldo=100;
	cp2->nome="POO";
	cp2->password="def";
	cp2->saldo=5;
	cp3->nome="LI3";
	cp3->password="ghi";
	cp3->saldo=20;
	insertGrowingArray(ga,cp1);
	insertGrowingArray(ga,cp2);
	insertGrowingArray(ga,cp3);
	printf("%d\n", ga->size);
	for(i=0; i<ga->size; i++){
		Utilizador aux=ga->Elems[i];
		printf("O nome de Utilizador é: %s\n", aux->nome);
		printf("A sua password é: %s\n", aux->password);
		printf("O seu saldo é: %d\n", aux->saldo);		
	}

	return 0;
}
*/

/*FUNCIONAL COM FGETS!!!

int main()
{
	int corta;
	int i;
	char* nome="N/A";
	char nm[100],pass[100];
	GrowingArray ga = initGrowingArray(10000);
	Utilizador cp1 = malloc(sizeof(struct user));
	Utilizador cp2 = malloc(sizeof(struct user));
	Utilizador cp3 = malloc(sizeof(struct user));
	cp1->nome="SO";
	cp1->password="abc";
	cp1->saldo=100;
	cp2->nome="POO";
	cp2->password="def";
	cp2->saldo=5;
	cp3->nome="LI3";
	cp3->password="ghi";
	cp3->saldo=20;
	insertGrowingArray(ga,cp1);
	insertGrowingArray(ga,cp2);
	insertGrowingArray(ga,cp3);
	printf("%d\n", ga->size);
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
		if(strcmp(aux->nome,nm) && strcmp(aux->password,pass)) {printf("BEM VINDO %s !!!\n", aux->nome);}
    }
	return 0;
}

*/