#ifndef UTIL_H
#define UTIL_H

#include "word_bank.h"

#define GRAY 0
#define YELLOW 1
#define GREEN 2
#define NONE 3

typedef struct {
    int result[WORD_LEN - 1];
    int result_as_int;
} Result;

extern void EvaluateResult(Result* result, const char* a, const char* b);

#endif