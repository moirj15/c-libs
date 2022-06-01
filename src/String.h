#ifndef STRING_H
#define STRING_H

#include "BasicTypes.h"

/// Both of these will include a NUL byte in the `data` array, which will also add to the total length.
typedef struct {
    char *data;
    u64 length;
} Str;

typedef struct {
    char *data;
    u64 length;
    u64 capacity;
} String;

String String_create(char *data);
String String_from_string(Str str);

void String_append_char(String string, char c);
void String_append_string(String string, Str st);
void String_append_dyn_string(String a, String b);

void String_destroy(String *string);

Str Str_from_c_string(const char *string);
Str Str_get_sub_string(Str str, u64 index);

#endif
