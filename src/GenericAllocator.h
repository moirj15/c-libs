#ifndef GENERICALLOCATOR_H_
#define GENERICALLOCATOR_H_

#include "BasicTypes.h"

void GenericAllocator_EnableDebugLog(bool enable);

void *_GenericAllocator_Malloc(u64 size, u64 line, const char *file_name);
void _GenericAllocator_Realloc(void **pointer, u64 new_size, u64 line, const char *file_name);
void _GenericAllocator_Free(void *pointer, u64 line, const char *file_name);

#define GenericAllocator_Malloc(size) _GenericAllocator_Malloc(size, __LINE__, __FILE__)
#define GenericAllocator_Realloc(pointer_address, new_size)                                                            \
    _GenericAllocator_Realloc((void **)pointer_address, new_size, __LINE__, __FILE__)
#define GenericAllocator_Free(pointer) _GenericAllocator_Free(pointer, __LINE__, __FILE__)

#endif // GENERICALLOCATOR_H_
