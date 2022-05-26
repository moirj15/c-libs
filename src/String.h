#ifndef STRING_H
#define STRING_H

#include "BasicTypes.h"
#include "Array.h"

typedef struct {
	char *data;
	u64 length;
} String;

typedef struct {
	DynamicArray(char) data;
	u64 length;
	u64 capacity;
} DynArray;

DynArray DynArray_create();
	

#endif
