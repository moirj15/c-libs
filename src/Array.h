#ifndef ARRAY_H_
#define ARRAY_H_

#include "BasicTypes.h"

#define DynamicArray(T) T *

void *_DynamicArray_Init(u64 element_size, u64 initial_capacity);

#define DynamicArray_Init(T, initial_capacity) _DynamicArray_Init(sizeof(T), initial_capacity);

void DynamicArray_GrowIfNeeded(void **array);
u64 DynamicArray_Size(void *array);
u64 DynamicArray_Capacity(void *array);

void _DynamicArray_IncrementSize(void *array);

#define DynamicArray_Append(array, ...)                                                                                \
    do {                                                                                                               \
        DynamicArray_GrowIfNeeded((void **)&array);                                                                    \
        array[DynamicArray_Size(array)] = __VA_ARGS__;                                                                 \
        _DynamicArray_IncrementSize(array);                                                                            \
    } while (0)

void DynamicArray_Destroy(void *array);

#endif // ARRAY_H_
