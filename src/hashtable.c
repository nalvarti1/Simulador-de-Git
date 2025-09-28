#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incs/hashtable.h"

// Funcion hasha polinomial

unsigned int hash_function(const char *key){
    unsigned int hash = 0;
    unsigned int p = 31;
    unsigned int p_pow = 1;

    while(*key){
        hash = (hash + ((unsigned char)(*key)*p_pow)) % HASH_TABLE_SIZE;
        p_pow = (p_pow * p) % HASH_TABLE_SIZE;
        key++;
    }

    return hash;
}

HashTable *Hash_create(){
    HashTable *table = malloc(sizeof(HashTable));
    if(!table)
        return NULL;
    // Inicializa todos los buckets en NULL
    for(int i = 0; i < HASH_TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    table->count = 0;

    return table;
}

void hash_destroy(HashTable *table){
    if(!table)
        return;

    for(int i = 0; i<HASH_TABLE_SIZE; i++){
        HashEntry *current = table->buckets[i];
        while(current){
            HashEntry *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(table);
}

bool hash_insert(HashTable *table, const char *key, void *value){
    if (!table || !key)
        return false;

    unsigned int index = hash_function(key);

    //Verifica si ya existe
    HashEntry *current = table->buckets[index];
    while(current){
        if(strcmp(current->key, key) == 0)
            current->value = value;
            return true;
    }
    current = current->next;

    //Crear nueva entrada
    HashEntry *new_entry = malloc(sizeof(HashEntry));
    if(!new_entry)
        return false;

    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;
    table->count++;

    return true;


}
