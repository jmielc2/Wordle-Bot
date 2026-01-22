//
// Created by jacob on 1/19/2026.
//

#include "wordle_bot.h"

#include <math.h>
#include <stdio.h>

static char* RESULT_TO_UNICODE[3] = { "\U00002B1B", "\U0001F7E8", "\U0001F7E9"};

typedef struct {
    char word[WORD_LEN];
    float value;
} Entropy;

static void PrintResult(const int result) {
    int v = result;
    for (int i = 0; i < 5; i++) {
        const int r = v % 3;
        printf("%s", RESULT_TO_UNICODE[r]);
        v -= r;
        v /= 3;
    }
    printf("\n");
}

static float ItEvaluator(const char* word, WB* wb) {
    float sum = 0.0f;
    int validCount = 0;
    int resultCountBuffer[MAX_RESULTS];
    GetResultCounts(wb, word, resultCountBuffer);
    for (int i = 0; i < MAX_RESULTS; i++) {
        const float p = (float) resultCountBuffer[i] / wb->total_word_count;
        if (p > 0.0f) {
            validCount += 1;
            sum += -log2(p) * p;
        }
    }
    return sum * validCount / wb->total_word_count;
}

static void SortEntropies(Entropy* entropyBuffer, const int low, const int high) {
    if (low == high) {
        return;
    }
    // Divide
    const int mid = (low + high) / 2;
    SortEntropies(entropyBuffer, low, mid);
    SortEntropies(entropyBuffer, mid + 1, high);

    // Merge
    int i = low, j = mid + 1, k = 0;
    Entropy mergeBuffer[high - low + 1];
    for (; k < high - low + 1; k++) {
        // Entropy a = entropyBuffer[i];
        // Entropy b = entropyBuffer[j];
        if (entropyBuffer[i].value < entropyBuffer[j].value && i <= mid) {
            mergeBuffer[k] = entropyBuffer[i];
            i++;
        } else if (j <= high) {
            mergeBuffer[k] = entropyBuffer[j];
            j++;
        } else {
            break;
        }
    }
    while (i <= mid) {
        mergeBuffer[k] = entropyBuffer[i];
        i++;
        k++;
    }
    memcpy(&entropyBuffer[low], mergeBuffer, high - low + 1 * sizeof(Entropy));
}

static void EvaluateNextGuess(WB* wb, char* nextGuess) {
    Entropy entropies[wb->total_word_count];
    Cursor cursor;
    CreateWordBankCursor(wb, &cursor);
    for (int i = 0; i < wb->total_word_count; i++) {
        strcpy(entropies[i].word, GetWord(&cursor));
        entropies[i].value = ItEvaluator(entropies[i].word, wb);
        MoveToNextWord(&cursor);
    }
    SortEntropies(entropies, 0, wb->total_word_count - 1);
    strcpy(nextGuess, entropies[wb->total_word_count - 1].word);
    DestroyWordBankCursor(&cursor);
}

void InitWordleBot(WordleBot* bot, WB* wb) {
    bot->wb = wb;
    EvaluateNextGuess(bot->wb, bot->first_guess);
}

void WordleBotSolvePuzzle(WordleBot* bot, Puzzle* puzzle) {

}