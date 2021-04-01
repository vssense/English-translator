#include "dynamic_array.h"

void Construct(DynamicArray* array, size_t capacity)
{
    assert(capacity);
    
    array->data = (Pair*)calloc(capacity, sizeof(Pair));
    assert(array->data);

    array->size = 0;
    array->capacity = capacity;
}

void Checkdata(DynamicArray* array)
{
    assert(array);

    if (array->size >= array->capacity - 1)
    {
        array->data = (Pair*)realloc(array->data, 
                                     array->capacity * 2 * sizeof(Pair));
        assert(array->data);
        array->capacity *= 2;
    }
}

void PushBack(DynamicArray* array, Pair elem)
{
    assert(array);
    assert(array->data);

    Checkdata(array);

    array->data[array->size] = elem;
    array->size++;
}

size_t GetSize(DynamicArray* array)
{
    assert(array);
    assert(array->data);

    return array->size;
}

void PopBack(DynamicArray* array)
{
    assert(array);
    assert(array->data);

    if (array->size == 0)
    {
        printf("You try to pop from empty array\n");
    }
    else
    {
        array->size--;
    }
}

Pair Back(DynamicArray* array)
{
    assert(array);
    assert(array->data);

    if (array->size > 0)
    {
        return array->data[array->size - 1];
    }
        
    printf("You try to back from empty array\n");
}

void Destruct(DynamicArray* array)
{
    assert(array);
    assert(array->data);

    if (array->capacity > 0)
    {
        free(array->data);
        array->capacity = 0;
    }

    array->size = 0;
}

void Dump(DynamicArray* array)
{
    assert(array);
    assert(array->data);

    printf("size = %lu\n", array->size);
    printf("capacity = %lu\n", array->capacity);

    for (size_t i = 0; i < array->size; ++i)
    {
        printf("%s",    array->data[i].key);
        printf("[%s] ", array->data[i].value);
    }

    printf("\n");
}