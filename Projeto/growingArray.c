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
