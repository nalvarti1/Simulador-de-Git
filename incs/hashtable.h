#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stdlib.h>

// Tamaño de la tabla hash (número primo para mejor distribución)
#define HASH_TABLE_SIZE 101

// Entrada individual de la tabla hash (nodo de lista enlazada)
typedef struct HashEntry{
    char *key;                    // Clave (ID del commit en nuestro caso)
    void *value;                  // Valor (puntero al objeto Commit)
    struct HashEntry *next;       // Siguiente entrada para resolver colisiones
} HashEntry;

// Estructura principal de la tabla hash
typedef struct HashTable{
    HashEntry *buckets[HASH_TABLE_SIZE]; // Array de punteros a listas enlazadas 
    int count;                           // Número total de elementos almacenados
} HashTable;



//=============== Funciones de la Tabla Hash ================================

// Función hash polinomial para convertir string a índice (0 a HASH_TABLE_SIZE-1)
unsigned int hash_function(const char *key);

// Funciones de creación y destrucción
HashTable *hash_create();                        // Crea e inicializa una nueva tabla hash
void hash_destroy(HashTable *table);            // Libera memoria de la tabla y todas sus entradas

// Operaciones CRUD de la tabla hash
bool hash_insert(HashTable *table, const char *key, void *value);  // Inserta/actualiza elemento 
void *hash_get(HashTable *table, const char *key);  // Busca elemento por clave
bool hash_remove(HashTable *table, const char *key); // Elimina elemento por clave 

// Funciones de utilidad
int hash_size(HashTable *table);    // Retorna número de elementos almacenados
bool hash_is_empty(HashTable *table);  // Verifica si la tabla está vacía


#endif