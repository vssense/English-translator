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

extern "C" __m256i CastTo__m256i(char* str)
{
    assert(str);

    char buffer[sizeof(__m256i)] = "";
    strcpy(buffer, str);
    return _mm256_loadu_si256((__m256i*)buffer);
}

void Insert(HashTable* table, value_type value, key_type key)
{
    assert(table);
    assert(table->data);

    __m256i value_ = CastTo__m256i(value);
    PushBack( table->data + (table->hash(&value) % table->size), {value_, key});
}

extern "C" key_type Find(HashTable* table, value_type value);
// {
//     DynamicArray* array = table->data + (table->hash(&value) % table->size); 
//     __m256i value_ = CastTo__m256i(value);

//     for (size_t i = 0; i < GetSize(array); ++i)
//     {
//         if ((~_mm256_movemask_epi8(_mm256_cmpeq_epi8(value_, array->data[i].value))) == 0)
//         {
//             return array->data[i].key;
//         }
//     }

//     return NULL;
// }

void Destruct(HashTable* table)
{
    assert(table);
    assert(table->data);

    for (size_t i = 0; i < table->size; ++i)
    {
        Destruct(table->data + i);
    }
}

void DestructWithBuffer(HashTable* table)
{
    assert(table);
    assert(table->data);

    for (size_t i = 0; i < table->size; ++i)
    {
        Destruct(table->data + i);
    }

    free(table->buffer);
}

void Dump(HashTable* table)
{
    printf("table size = %lu\n", table->size);

    for (size_t i = 0; i < table->size; ++i)
    {
        Dump(table->data + i);
    }
}

void PrintBucketSizes(HashTable* table, FILE* file)
{
    for (size_t i = 0; i < table->size - 1; ++i)
    {
        fprintf(file, "%lu\n", table->data[i].size);
    }

    fprintf(file, "%lu\n", table->data[table->size - 1].size);
}