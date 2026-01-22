#ifndef UTIL_H
#define UTIL_H

typedef struct Result Result;

#include "word_bank.h"

#define GRAY 0
#define YELLOW 1
#define GREEN 2
#define NONE 3

#define MAX_RESULTS 243  // 3^5

struct Result {
    int result[WORD_LEN - 1];
    int result_as_int;
};

extern void EvaluateResult(Result* result, const char* a, const char* b);

#endif