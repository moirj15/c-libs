#include "GenericAllocator.h"

#include <stdio.h>
#include <stdlib.h>

static bool _GenericAllocator_logging_enabled = false;

void GenericAllocator_EnableDebugLog(bool enable)
{
    _GenericAllocator_logging_enabled = enable;
}

void *_GenericAllocator_Malloc(u64 size, u64 line, const char *file_name)
{
    void *pointer = NULL;
    pointer = malloc(size);
    if (!pointer && _GenericAllocator_logging_enabled) {
        printf("Failed to allocate %llx bytes in file %s at line %llu\n", size, file_name, line);
    } else if (pointer) {
        printf("%p : BYTES %llx, FILE %s, LINE %llu\n", pointer, size, file_name, line);
    }
    return pointer;
}

void _GenericAllocator_Realloc(void **pointer, u64 new_size, u64 line, const char *file_name)
{
    void *new_pointer = NULL;
    new_pointer = realloc(*pointer, new_size);
    if (!new_pointer && _GenericAllocator_logging_enabled) {
        printf("Failed to allocate %llx bytes in file %s at line %llu\n", new_size, file_name, line);
    } else if (new_pointer == *pointer && _GenericAllocator_logging_enabled) {
        printf("%p : RESIZED BYTES %llx, FILE %s, LINE %llu\n", *pointer, new_size, file_name, line);
    } else if (new_pointer != *pointer && _GenericAllocator_logging_enabled) {
        printf("%p : RE-ALLOCATED TO %p WITH BYTES %llu, FILE %s, LINE %llu\n", *pointer, new_pointer, new_size,
            file_name, line);
        *pointer = new_pointer;
    }
}

void _GenericAllocator_Free(void *pointer, u64 line, const char *file_name)
{
    if (_GenericAllocator_logging_enabled) {
        printf("%p : FREE'D AT FILE %s, LINE %llu\n", pointer, file_name, line);
    }
    free(pointer);
}
