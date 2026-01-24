//
// Created by jacob on 1/19/2026.
//

#include "wordle_bot.h"
#include "puzzle.h"

#include <math.h>
#include <stdio.h>

static const char* RESULT_TO_UNICODE[3] = { "a", "b", "c" };

typedef struct {
    char word[WORD_LEN];
    float value;
} Entropy;

static void PrintResult(const int result) {
    int v = result;
    for (int i = 0; i < 5; i++) {
        const int r = v % 3;
        printf(RESULT_TO_UNICODE[r]);
        v -= r;
        v /= 3;
    }
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
    const int numElements = high - low + 1;
    int i = low, j = mid + 1, k = 0;
    Entropy mergeBuffer[numElements];
    for (; k < numElements; k++) {
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
    memcpy(&entropyBuffer[low], mergeBuffer, numElements * sizeof(Entropy));
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
    printf("Initializing Wordle Bot...\n");
    bot->wb = wb;
    EvaluateNextGuess(bot->wb, bot->first_guess);
}

void WordleBotSolvePuzzle(WordleBot* bot, Puzzle* puzzle) {
    char guess[WORD_LEN];
    Result result;
    WB tempCopy;
    strcpy(guess, bot->first_guess);

    while (!PuzzleGameIsOver(puzzle)) {
        if (puzzle->num_guesses > 0) {
            EvaluateNextGuess(&bot->_wb_working_copy, guess);
            PuzzleMakeGuess(puzzle, guess, &result);
            RefineWordBank(&bot->_wb_working_copy, guess, &result, &tempCopy);
            bot->_wb_working_copy = tempCopy;
        } else {
            PuzzleMakeGuess(puzzle, guess, &result);
            RefineWordBank(bot->wb, guess, &result, &bot->_wb_working_copy);
        }
        // PrintResult(result.result_as_int);
        // printf(" -> %s\n", guess);
    }

    if (PuzzleGameIsWon(puzzle)) {
        printf("Hooray, wordle bot guessed %s in %i tries!\n", PuzzleGetLastGuess(puzzle), puzzle->num_guesses);
    } else {
        printf("Oh no! Wordle bot didn't guess %s within %i tries :(\n", puzzle->word, NUM_GUESSES);
    }
    printf("\n");
}