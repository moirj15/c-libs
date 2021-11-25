#include "Array.h"
#include "GenericAllocator.h"

#include <stdio.h>

typedef struct {
    f32 a;
    u32 b;
    u8 c;
} foo;
int main(int argc, char **argv)
{
    GenericAllocator_EnableDebugLog(true);
    DynamicArray(foo) array = DynamicArray_Init(foo, 32);
    for (int i = 0; i < 64; i++) {
        foo f = {.a = i * i, .b = i, .c = i};
        DynamicArray_Append(array, f);
    }
    printf("size %ld\n", DynamicArray_Size(array));
    printf("capacity %ld\n", DynamicArray_Capacity(array));
    for (int i = 0; i < DynamicArray_Size(array); i++) {
        printf("Array[%d] = {%f, %d, %d}\n", i, array[i].a, array[i].b, array[i].c);
    }

    DynamicArray_Destroy(array);
    return 0;
}
