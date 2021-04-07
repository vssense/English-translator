#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

static const size_t list_start_capacity = 4;

struct HashTable
{
    DynamicArray* data = nullptr;
    size_t size = 0;
    size_t (*hash)(const value_type* elem) = nullptr;
    int    (*cmp) (const value_type* value1, const value_type* value2);
    char* buffer = nullptr;
};

void     Construct         (HashTable* table, size_t size, size_t (*hash)(const value_type* elem),
                                              int (*cmp)(const value_type* value1, const value_type* value2));                               
void     Insert            (HashTable* table, value_type value, key_type key);
key_type Find              (HashTable* table, value_type value);
void     PrintBucketSizes  (HashTable* table, FILE* file);
void     Dump              (HashTable* table);
void     Destruct          (HashTable* table);
void     DestructWithBuffer(HashTable* table);
