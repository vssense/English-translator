#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
#include <string.h>

typedef char* key_type;
typedef char* value_type;

struct Pair
{
	__m256i value;
	key_type key;
	key_type key1;
	key_type key2;
	key_type key3;
};

struct DynamicArray
{
    Pair*  data     = nullptr;
    size_t size     = 0;
    size_t capacity = 0;
};

void   Construct(DynamicArray* array, size_t capacity);
void   PushBack (DynamicArray* array, Pair elem);
size_t GetSize  (DynamicArray* array);
void   PopBack  (DynamicArray* array);
Pair   Back     (DynamicArray* array);
void   Dump     (DynamicArray* array);
void   Destruct (DynamicArray* array);
