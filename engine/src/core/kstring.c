#include "core/kstring.h"
#include "core/kmemory.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

u64 string_length(const char* str) {
    return strlen(str);
}
char* string_duplicate(const char* str) {
    u64 length = string_length(str);
    char* copy = kallocate(length + 1, MEMORY_TAG_STRING);
    kcopy_memory(copy, str, length + 1);
    return copy;
}

// Case-sensitive string comparison. True if same, otherwise false.
b8 strings_equal(const char* str0, const char* str1) {
    return strcmp(str0, str1) == 0;
}

// Performs string formattingg to dest given format string and parameters.
KAPI i32 string_format(char* dest, const char* format, ...) {
    if (dest && format) {
        va_list arg_ptr;
        va_start(arg_ptr, format);
        i32 written = string_format_v(dest, format, arg_ptr);
        va_end(arg_ptr);
        return written;
    }
    return -1;
}

KAPI i32 string_format_v(char* dest, const char* format, va_list args) {
    if (dest && format) {
        // Big but can fit on the stack.
        char buffer[32000];
        i32 written = vsnprintf(buffer, 32000, format, args);

        if (written < 0) {
            return -1;
        }

        // Clamp to buffer size - 1 to avoid overflow 
        if (written >= (i32)sizeof(buffer)) {
            written = sizeof(buffer) - 1;
        }

        buffer[written] = '\0';
        kcopy_memory(dest, buffer, written + 1);

        return written;
    }
    return -1;
}

