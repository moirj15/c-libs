#include "String.h"

#include "GenericAllocator.h"

#include <string.h>

String String_create_null()
{
    return (String){
        .data = NULL,
        .length = 0,
        .capacity = 0,
    };
}

void String__realloc_if_needed(String *string, u64 new_length)
{
    if (new_length > string->capacity) {
        // TODO: figure out a growth scheme
        string->capacity = new_length + 256;
        GenericAllocator_Realloc(&string->data, string->capacity);
    }
}

String String_create(char *data)
{
    String ret = String_create_null();
    if (data != NULL) {
        ret.length = strlen(data);
        ret.capacity = ret.length;
        ret.data = GenericAllocator_Malloc(ret.length);
        memset(ret.data, 0, ret.length);
    }
    return ret;
}

String String_from_string(Str str)
{
    String ret = String_create_null();
    if (str.length > 0) {
        ret.length = str.length;
        ret.capacity = str.length;
        ret.data = GenericAllocator_Malloc(str.length);
        memset(ret.data, 0, str.length);
        memcpy(ret.data, str.data, str.length);
    }
    return ret;
}

void String_append_char(String string, char c)
{
    String__realloc_if_needed(&string, string.length + 1);
    string.data[string.length] = c;
    string.data[string.length + 1] = 0;
}

void String_append_string(String string, Str str)
{
    String__realloc_if_needed(&string, str.length + string.length);
    memcpy(string.data + string.length - 1, str.data, str.length);
}

void String_append_dyn_string(String a, String b)
{
    String_append_string(a, b);
}

void String_destroy(String *string)
{
}

Str Str_from_c_string(const char *string)
{
}

Str Str_get_sub_string(Str str, u64 index)
{
}
