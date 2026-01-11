#include "util.h"
#include <string.h>

static int CharIndexInWord(const char a, const char* word) {
    for (int i = 0; i < WORD_LEN - 1; i++) {
        if (a == word[i]) {
            return i;
        }
    }
    return -1;
}

static int EvaluateResultAsInt(const int* resultArray) {
    int base = 1;
    int result = 0;
    for (int i = 0; i < WORD_LEN - 1; i++) {
        result += base * resultArray[i];
        base *= 3;
    }
    return result;
}

void EvaluateResult(Result* result, const char* a, const char* b) {
    memset(result->result, GRAY, sizeof(result->result));
    char word[WORD_LEN - 1];
    char guess[WORD_LEN - 1];
    memcpy(&word, b, sizeof(word));
    memcpy(&guess, a, sizeof(guess));
    for (int i = 0; i < WORD_LEN - 1; i++) {
        const char letter = guess[i];
        if (letter == word[i]) {
            word[i] = NONE;
            guess[i] = NONE;
            result->result[i] = GREEN;
        }
    }
    for (int i = 0; i < WORD_LEN - 1; i++) {
        const char letter = guess[i];
        const int letterIndex = CharIndexInWord(letter, word);
        if (letter != NONE && letterIndex != -1) {
            result->result[i] = YELLOW;
            word[letterIndex] = NONE;
        }
    }
    result->result_as_int = EvaluateResultAsInt(result->result);
}
