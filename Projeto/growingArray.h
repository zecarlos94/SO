#ifndef GROWINGARRAY_H

#define GROWINGARRAY_H

typedef struct user {
        char* nome;
        char* password;
        int saldo;
}Users;

typedef struct user *Utilizadores;

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