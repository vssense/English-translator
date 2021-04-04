#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef char* key_type;
typedef char* value_type;

struct Pair
{
	value_type value;
	key_type key;
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
