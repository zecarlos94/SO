/*so.h*/

#define VECTOR_INITIAL_CAPACITY 100

/* Define a vector type*/
typedef struct {
  int size;      // slots used so far
  int capacity;  // total available slots
  char **nomes;
  char **passwords; 
  int *saldos; 
} Vector;

void vector_init(Vector *vector);

void vector_append(Vector *vector, char *nome, char *password, int saldo);

char * vector_getNomes(Vector *vector, int index);

char * vector_getPasswords(Vector *vector, int index);

int vector_getSaldos(Vector *vector, int index);

void vector_set(Vector *vector, int index, char *nome, char *password, int saldo);

void vector_double_capacity_if_full(Vector *vector);

void vector_free(Vector *vector);