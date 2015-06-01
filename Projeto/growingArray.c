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
	novo->clientes = calloc(max_size,sizeof(Clientes));
	return novo;
}

void insertContabilidade(Contabilidade a, Cliente o) {
	if(a->size==a->max_size) {
		a->max_size*=1.5; 
		a->clientes =realloc(a->clientes, sizeof(void*) *  a->max_size);
	}	
	a->Clientes[a->size]=o;
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
	for(i=0;i < Contabilidade->size;i++)
		if( contabilidade->clientes[i]->pid == pid) cliente = contabilidade->clientes[i]
	return cliente;
}

	

	
