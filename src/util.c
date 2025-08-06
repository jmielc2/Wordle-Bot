#include "util.h"

FILE* open_file(const char* filename, const char* mode) {
    return fopen(filename, mode);
}

int seek_file(FILE* file, long offset, int whence) {
    return fseek(file, offset, whence);
}

long tell_file(FILE* file) {
    return ftell(file);
}

size_t read_file(void* dest, size_t size, size_t num_items, FILE* file) {
    return fread(dest, size, num_items, file);
}

int close_file(FILE* file) {
    return fclose(file);
}

