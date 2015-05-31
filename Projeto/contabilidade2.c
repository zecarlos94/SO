#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "contabilidade.h"

#define SALDO 20


Contabilidade initContabilidade(int max_size) {
	Contabilidade novo = malloc(sizeof(struct contabilidade));
	novo->size = 0;
	novo->max_size = max_size;
	novo->clientes = calloc(max_size,sizeof(Cliente));
	return novo;
}

void insertContabilidade(Contabilidade a, Cliente o) {
	if(a->size==a->max_size) {
		a->max_size*=1.5; 
		a->clientes =realloc(a->clientes, sizeof(void*) *  a->max_size);
	}	
	a->clientes[a->size]=o;
	a->size+=1;
}

void criaConta(Contabilidade cont,int pid,int memoria_comprada) {
	Cliente c = malloc(sizeof(cliente));
	c->pid = pid;
	c->saldo = SALDO;
	c->memoria_utilizada = 0;
	c->memoria_comprada = memoria_comprada;
	insertContabilidade(cont,c); 
}

Cliente dadosCliente(Contabilidade c,int pid) {
	int i;
	Cliente cliente=NULL;
	for(i=0;i < c->size;i++)
		if( c->clientes[i]->pid == pid) cliente = c->clientes[i];
	return cliente;
}

/*
	
int main()
{
	int i;
	Contabilidade ct = initContabilidade(10000);
	criaConta(ct,1234,30);
	criaConta(ct,5678,12);
	criaConta(ct,9012,45);
	criaConta(ct,4920,26);

	for(i=0; i<ct->size; i++){
		Cliente aux=ct->clientes[i];
		printf("BEM VINDO %d !!!\n", aux->pid);
		printf("O seu saldo é: %d\n", aux->saldo);
		printf("A memória utilizada foi: %d\n", aux->memoria_utilizada);
		printf("A memória comprada foi:%d\n", aux->memoria_comprada);
    }
	return 0;
}
*/	
