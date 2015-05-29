#ifndef GROWINGARRAY_H

#define GROWINGARRAY_H

typedef struct client {
        int pid_number;
        int saldo;
}Clients;

typedef struct client *Clientes;

typedef void* Objeto;

typedef struct growingarray{
        Objeto* Elems;
        int size;
        int max_size;
} growingarray;

typedef growingarray* GrowingArray;

GrowingArray initGrowingArray(int max_size);

void insertGrowingArray(GrowingArray a, Objeto o);

void ordenaArrayAux(int **arrayAux, int length);

void qSort(int **arrayAux, int left, int right);

#endif