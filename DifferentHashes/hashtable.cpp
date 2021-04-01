#include "hashtable.h"

void Construct(HashTable* table, size_t size, size_t (*hash)(const value_type* elem),
               int (*cmp)(const value_type* value1, const value_type* value2))
{
    assert(table);

    table->data = (DynamicArray*)calloc(size, sizeof(DynamicArray));

    for (size_t i = 0; i < size; ++i)
    {
        Construct(table->data + i, list_start_capacity);
    }

    table->size = size;
    table->hash = hash;
    table->cmp = cmp;
}

void Insert(HashTable* table, value_type value, key_type key)
{
    assert(table);
    assert(table->data);

    PushBack(table->data + (table->hash(&value) % table->size), {value, key});
}

key_type Find(HashTable* table, value_type value)
{
    DynamicArray* array = table->data + (table->hash(&value) % table->size); 
    for (size_t i = 0; i < GetSize(array); ++i)
    {
        if (table->cmp(&value, &array->data[i].value) == 0)
        {
            return array->data[i].key;
        }
    }

    return NULL;
}

void Destruct(HashTable* table)
{
    assert(table);
    assert(table->data);

    for (size_t i = 0; i < table->size; ++i)
    {
        Destruct(table->data + i);
    }
}

void Dump(HashTable* table)
{
    printf("table size = %lu\n", table->size);

    for (size_t i = 0; i < table->size; ++i)
    {
        Dump(table->data + i);
    }
}