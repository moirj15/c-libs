#include "Array.h"

#include "GenericAllocator.h"

#include <string.h>

typedef struct {
    u64 element_size;
    u64 capacity;
    u64 size;
} DynamicArrayHeader;

DynamicArrayHeader *_DynamicArray_GetHeader(void *array)
{
    return ((DynamicArrayHeader *)(array - sizeof(DynamicArrayHeader)));
}

void *_DynamicArray_Init(u64 element_size, u64 initial_capacity)
{
    const u64 total_size = sizeof(DynamicArrayHeader) + (element_size * initial_capacity);
    DynamicArrayHeader *data = (DynamicArrayHeader *)GenericAllocator_Malloc(total_size);
    memset(data, 0, total_size);
    data->element_size = element_size;
    data->capacity = initial_capacity;

    return ((void *)data) + sizeof(DynamicArrayHeader);
}

void DynamicArray_GrowIfNeeded(void **array)
{
    DynamicArrayHeader *data = (*array) - sizeof(DynamicArrayHeader);
    if (data->capacity < (data->size + 1)) {
        data->capacity += 32;
        GenericAllocator_Realloc(&data, sizeof(DynamicArrayHeader) + (data->element_size * data->capacity));
        *array = (void *)data + sizeof(DynamicArrayHeader);
    }
}

u64 DynamicArray_Size(void *array)
{
    return _DynamicArray_GetHeader(array)->size;
}

u64 DynamicArray_Capacity(void *array)
{
    return _DynamicArray_GetHeader(array)->capacity;
}

void _DynamicArray_IncrementSize(void *array)
{
    _DynamicArray_GetHeader(array)->size++;
}

void DynamicArray_Destroy(void *array)
{
    GenericAllocator_Free(_DynamicArray_GetHeader(array));
}
