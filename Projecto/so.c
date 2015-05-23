/*so.c*/

#include <stdio.h>
#include <stdlib.h>
#include "so.h"

static int tamanho = 0;

void vector_init(Vector *vector) {
  /* initialize size and capacity*/
  vector->size = 0;
  vector->capacity = VECTOR_INITIAL_CAPACITY;

  /* allocate memory for vector->nomes*/
  vector->nomes = malloc(sizeof(char *) * vector->capacity);
  vector->passwords = malloc(sizeof(char *) * vector->capacity);
  vector->saldos = malloc(sizeof(int) * vector->capacity);

}

void vector_append(Vector *vector, char *nome, char *password, int saldo) {
  /* make sure there's room to expand into*/
  vector_double_capacity_if_full(vector);

  /* append the nomes and increment vector->size
  vector->nomes[vector->size] = nome;
  vector->passwords[vector->size] = password;
  vector->saldos[vector->size] = saldo;
  vector->size++;*/
  vector->nomes[tamanho] = nome;
  vector->passwords[tamanho] = password;
  vector->saldos[tamanho] = saldo;
  tamanho++;
}

char * vector_getNomes(Vector *vector, int index) {
  /*if (index >= vector->size || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
    exit(1);*/
  if (index >= tamanho || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, tamanho);
    exit(1);
  }
  return vector->nomes[index];
}

char * vector_getPasswords(Vector *vector, int index) {
  /*if (index >= vector->size || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
    exit(1);*/
  if (index >= tamanho || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, tamanho);
    exit(1);
  }
  return vector->passwords[index];
}

int vector_getSaldos(Vector *vector, int index) {
  /*if (index >= vector->size || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
    exit(1);*/
  if (index >= tamanho || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, tamanho);
    exit(1); 
  }
  return vector->saldos[index];
}

void vector_set(Vector *vector, int index, char *nome, char *password, int saldo) {
  /* zero fill the vector up to the desired index*/
  /*while (index >= vector->size)*/ 
  while (index >= tamanho){
    vector_append(vector, 0, 0, 0);
  }

  /* set the nomes at the desired index*/
  vector->nomes[index] = nome;
  vector->passwords[index] = password;
  vector->saldos[index] = saldo;
}

void vector_double_capacity_if_full(Vector *vector) {
  if (vector->size >= vector->capacity) {
    /* double vector->capacity and resize the allocated memory accordingly*/
    vector->capacity *= 2;
    vector->nomes = realloc(vector->nomes, sizeof(char *) * vector->capacity);
    vector->passwords = realloc(vector->passwords, sizeof(char *) * vector->capacity);
    vector->saldos = realloc(vector->saldos, sizeof(int) * vector->capacity);
  }
}

void vector_free(Vector *vector) {
  free(vector->nomes);
  free(vector->passwords);
  free(vector->saldos);
}