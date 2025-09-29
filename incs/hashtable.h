#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 101

// Entrada individual de la tabla hash
typedef struct HashEntry{
    char *key; // Clave nombre del archivo
    void *value; // Valor
    struct HashEntry *next; // Para resolver colsiones
} HashEntry;

// Estructura principal de la tabla hash
typedef struct HashTable{
    HashEntry *buckets[HASH_TABLE_SIZE]; // Array de buckets
    int count; // Número de elementos
} HashTable;



//=============== Funciones================================

// Funcion hash para convertir string  a indice
unsigned int hash_function(const char *key);

//Crear y destruir tabla hash
HashTable *hash_create();
void hash_destroy(HashTable *table);

//Inserta un elemento en la tabla hash
bool hash_insert(HashTable *table, const char *key, void *value);
void *hash_get(HashTable *table, const char *key);
bool hash_remove(HashTable *table, const char *key);
int hash_size(HashTable *table);
bool hash_is_empty(HashTable *table);


#endif