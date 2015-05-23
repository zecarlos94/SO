/*vectorSo.c*/

#include <stdio.h>
#include "so.c"

#define MAX 1000

int main() {
 
  Vector vector;
  vector_init(&vector);
  int tamanho_antes = 0;
  tamanho_antes = vector.size;
  printf("%d\n", tamanho_antes);
  char * nome = "Olá";
  char * password = "0123456789";
  int i;
  for (i=0; i<MAX/2; i++) {
    vector_append(&vector, nome, password, MAX-i);
  }
  nome="SO!!!";
  password="9876543210";
  for (i=MAX/2; i<MAX; i++) {
    vector_append(&vector, nome, password, MAX-i);
  }
  int tamanho_depois = 0;
  tamanho_depois = vector.size;
  printf("%d\n", tamanho_depois);
  printf("Nome na Posição 30: %s\n", vector_getNomes(&vector, 30));
  printf("Password na Posição 30: %s\n", vector_getPasswords(&vector, 30));
  printf("Saldo na Posição 30: %d\n", vector_getSaldos(&vector, 30));
  printf("Nome na Posição 900: %s\n", vector_getNomes(&vector, 900));
  printf("Password na Posição 900: %s\n", vector_getPasswords(&vector, 900));
  printf("Saldo na Posição 900: %d\n", vector_getSaldos(&vector, 900));
  vector_free(&vector);
}