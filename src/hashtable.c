#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incs/hashtable.h"

//Función hash polinomial para distribución uniforme de claves
//Convierte string de commit ID a índice de tabla (0 a HASH_TABLE_SIZE-1)
unsigned int hash_function(const char *key){
    unsigned int hash = 0;           // Valor hash acumulado
    unsigned int p = 31;             // Base polinomial (número primo)
    unsigned int p_pow = 1;          // Potencia actual de la base

    // Procesar cada carácter del string
    while(*key){ // Mientras no sea '\0'
        // Fórmula: hash = (a[0] + a[1]*p + a[2]*p^2 + ... + a[n]*p^n) mod HASH_TABLE_SIZE
        hash = (hash + ((unsigned char)(*key) * p_pow)) % HASH_TABLE_SIZE;
        p_pow = (p_pow * p) % HASH_TABLE_SIZE;  // Siguiente potencia
        key++;
    }

    // Retorna índice final (0 a HASH_TABLE_SIZE-1)
    return hash;
}

//Crea e inicializa una nueva tabla hash vacía
HashTable *hash_create(){

    HashTable *table = malloc(sizeof(HashTable));
    if(!table)
        return NULL;
    
    // Inicializar todos los buckets como listas vacías
    for(int i = 0; i < HASH_TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    
    table->count = 0;  // Tabla inicialmente vacía

    return table;
}

//Libera TODA la memoria utilizada por la tabla hash
//Recorre cada y libera sus listas enlazadas
void hash_destroy(HashTable *table){

    //Validacion: Si table es NULL, no hay nada que liberar 
    if(!table)
        return;
     // Recorrer TODOS los buckets de la tabla (0 a HASH_TABLE_SIZE-1)
    // Cada bucket puede tener: NULL (vacío) o lista enlazada con elementos
    for(int i = 0; i<HASH_TABLE_SIZE; i++){
        
        //Obtiene el primer nodo del bucket actual
        HashEntry *current = table->buckets[i];

        //Libera la lista enlazada del bucket
        while(current){
            //Guarda el puntero al siguiente antes de liberar "current"
            HashEntry *next = current->next;
            //Libera el string de la clave (key) creado en hash_insert
            free(current->key);
            //Libera el nodo actual de la lista
            free(current);
            //Avanza al siguiente nido usando la copia guardada
            current = next;
        }
        //Despues del while, la lista del bucket[i] esta liberada
        //Bucket[i] apunta a "basura"
        //Despues se libera la tabla
    }
    //Libera la estructura principal HashTable
    free(table);
}

bool hash_insert(HashTable *table, const char *key, void *value){
//Insercion en tabla hash

    //Validacion de parametros
    //Si table y key son NULL retorna false
    if (!table || !key)
        return false;

    //Calcula la posicion en la tabla con hash_function()
    //Convierte el string a un indice (0-100)
    //ejemplo: "abc123ef" = 42 en la tabla hash
    unsigned int index = hash_function(key);

    //Verifica si la clave ya existe
    //Obtiene el primer nodo del bucket[index]
    HashEntry *current = table->buckets[index];

    //Recorre la lista enlazada del bucket
    while(current){
        //Verifica si la clave actual es igual a la que se quiere insertar
        if(strcmp(current->key, key) == 0){
            //Si es asi, se actualiza el valor
            current->value = value;
            //Actualizado -> True
            return true;
        }
        //No es igual, avanza al siguiente nodo
        current = current->next;
    }
    //La clave no existe -> se crea una nueva entrada
    
    //Se reserva memoria para el nuevo nodo
    HashEntry *new_entry = malloc(sizeof(HashEntry));
    if(!new_entry)
        return false; //Sin memoria disponible

    //===========Nuevo nodo================
    //strdup duplica la clave creando una copia independiente 
    new_entry->key = strdup(key);
    //Asigna el valor
    new_entry->value = value;
    //Se inserta al inicio de la lista
    //El nodo nuevo apunta al que era el primer nodo
    new_entry->next = table->buckets[index];
    //El bucket ahora apunta al nuevo nodo (nuevo primero)
    table->buckets[index] = new_entry;
    //Actualiza el contador de elementos
    table->count++;

    //Insercion -> True
    return true; 
}

void *hash_get(HashTable *table, const char *key){
    //Busqueda en la tabla hash. Encuentra un elemento por su clave.

    //Validacion de parametros
    if (!table || !key)
        return NULL;

    //Calcula la posicion exacta con hash_function()
    unsigned int index = hash_function(key);

    //Va directamente al bucket correcto sin tener que recorrer toda la tabla
    //busqueda O(1) 
    HashEntry *current = table->buckets[index];

    //Busca dentro de la lista de elementos del bucket 
    while (current) {
        //Compara las claves
        if (strcmp(current->key, key) == 0) {
            //Clave encontrada:
            //Retorna el valor que esta asociado
            return current->value; //Puntero al commit
        }
        //si no es la clave correcta, pasa el siguiente elemento
        current = current->next;
    }
    //NO ENCONTRADO
    //Si recorre toda la lista del bucket y no encuentra el elemento
    //El elemento no existe y retorna NULL
    return NULL;
}

bool hash_remove(HashTable *table, const char *key){
//Elimina un elemento de la tabla hash por su clave

    //Validacion de parametros
    if (!table || !key)
       return false;

    //Calcula la posicion con hash_function()
    unsigned int index = hash_function(key);

    //Uso de punteros para el recorrido
    HashEntry *current = table->buckets[index]; //Nodo actual
    HashEntry *prev = NULL;                     //Nodo anterior

    //Busca el elemento manteniendo el rastro del anterior
    while(current){
        //Compara las claves
        if(strcmp(current->key, key)==0){

            //Elemento en medio o al final de la lista
            //Reconecta anterior y siguiente
            if(prev)
                prev->next = current->next;

            //Elemento al inicio de la lista
            //El bucket debe apuntar al siguiente
            else    
                table->buckets[index] = current->next;
            
            //Liberar memoria del elemento eliminado
            free(current->key); //Libera el string
            free(current); //Libera el nodo
            table->count--; //Actualiza el numero de elementos
            return true; //Eliminacion -> True
        }

        //No es el elemento buscado
        //Avanza manteniendo el rastro

        //El nodo actual ahora es el anterior
        prev = current;
        //avanza al siguiente
        current = current-> next;
    
    }
    //Elemento no encontrado
    return false;
}

int hash_size(HashTable *table){
//Obtener el numero de elementos de la tabla
    if (table != NULL)
        return table->count;
    return 0;
}

bool hash_is_empty(HashTable *table) {
//Verifica si la tabla hash esta vacia
    if (table != NULL) {
        return table->count == 0;
    } 
    return true;
}
