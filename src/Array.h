#ifndef ARRAY_H_
#define ARRAY_H_

#include "BasicTypes.h"

#define DynamicArray(T) T *

u8 *_DynamicArray_init(u64 element_size, u64 initial_capacity);

#define DynamicArray_init(T, initial_capacity) (T *)_DynamicArray_init(sizeof(T), initial_capacity)

u8 *_DynamicArray_init_with_size(u64 element_size, u64 size);
#define DynamicArray_init_with_size(T, size) (T *)_DynamicArray_init_with_size(sizeof(T), size)

void DynamicArray_grow_if_needed(u8 **array);
u64 _DynamicArray_size(u8 *array);
#define DynamicArray_size(array) _DynamicArray_size((u8 *)array)
u64 DynamicArray_capacity(u8 *array);

void _DynamicArray_increment_size(u8 *array);

#define DynamicArray_append(array, ...)                                                                                \
    do {                                                                                                               \
        DynamicArray_GrowIfNeeded((u8 **)&array);                                                                      \
        array[DynamicArray_size(array)] = __VA_ARGS__;                                                                 \
        _DynamicArray_IncrementSize(array);                                                                            \
    } while (0)

void DynamicArray_destroy(void *array);

#endif // ARRAY_H_
