#ifndef GROWINGARRAY_H

#define GROWINGARRAY_H

typedef struct cliente {
        int pid;
        int saldo;
	int memoria_utilizada;
	int memoria_comprada;
	char pipe[20];
}cliente;

typedef cliente* Cliente;

typedef struct contabilidade{
        Cliente* clientes;
        int size;
        int max_size;
} contabilidade;

typedef contabilidade* Contabilidade;

Contabilidade initContabilidade(int size);

void insertContabilidade(Contabilidade a, Cliente c);

void criaConta(Contabilidade c,int pid,int memoria_comprada,char* pipe);

Cliente dadosCliente(Contabilidade c,int pid);



#endif
