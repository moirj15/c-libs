#include "Array.h"

#include "GenericAllocator.h"

#include <string.h>
#include <assert.h>

typedef struct {
    u64 element_size;
    u64 capacity;
    u64 size;
} DynamicArrayHeader;

DynamicArrayHeader *_DynamicArray_GetHeader(u8 *array)
{
    return ((DynamicArrayHeader *)(array - sizeof(DynamicArrayHeader)));
}

u8 *_DynamicArray_init(u64 element_size, u64 initial_capacity)
{
    const u64 total_size = sizeof(DynamicArrayHeader) + (element_size * initial_capacity);
    DynamicArrayHeader *data = (DynamicArrayHeader *)GenericAllocator_Malloc(total_size);
    memset(data, 0, total_size);
    data->element_size = element_size;
    data->capacity = initial_capacity;

    return ((u8 *)data) + sizeof(DynamicArrayHeader);
}

u8 *_DynamicArray_init_with_size(u64 element_size, u64 size)
{
    u8 *array = _DynamicArray_init(element_size, size);
    _DynamicArray_GetHeader(array)->size = size;
    return array;
}

void DynamicArray_grow_if_needed(u8 **array)
{
    DynamicArrayHeader *data = (DynamicArrayHeader *)((*array) - sizeof(DynamicArrayHeader));
    if (data->capacity < (data->size + 1)) {
        data->capacity += 32;
        GenericAllocator_Realloc(&data, sizeof(DynamicArrayHeader) + (data->element_size * data->capacity));
        *array = (u8 *)data + sizeof(DynamicArrayHeader);
    }
}

u64 _DynamicArray_size(u8 *array)
{
    return _DynamicArray_GetHeader(array)->size;
}

u64 DynamicArray_capacity(u8 *array)
{
    return _DynamicArray_GetHeader(array)->capacity;
}

void _DynamicArray_increment_size(u8 *array)
{
    _DynamicArray_GetHeader(array)->size++;
}

void DynamicArray_destroy(void *array)
{
    GenericAllocator_Free(_DynamicArray_GetHeader(array));
}
