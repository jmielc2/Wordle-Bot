#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

// Wrappers around system calls. Used for mocking in tests

FILE* open_file(const char* filename, const char* mode);

int seek_file(FILE* file, long offset, int whence);

long tell_file(FILE* file);

size_t read_file(void* dest, size_t size, size_t num_items, FILE* file);

int close_file(FILE* file);

#endif