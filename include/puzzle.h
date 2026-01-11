#ifndef PUZZLE_H
#define PUZZLE_H

#include <string.h>

#include "util.h"
#include "word_bank.h"

#define NUM_GUESSES 5

typedef struct {
    Result result;
    char guess[WORD_LEN];
} GuessHistoryEntry;

typedef struct {
    char word[WORD_LEN];
    GuessHistoryEntry _guesses[NUM_GUESSES];
    int num_guesses;
} Puzzle;

extern void InitPuzzle(Puzzle* puzzle, const char* word);

extern void ResetPuzzle(Puzzle* puzzle, const char* word);

extern char* PuzzleGetGuess(Puzzle* puzzle, int index);

extern char* PuzzleGetLastGuess(Puzzle* puzzle);

extern int PuzzleGameIsWon(Puzzle* puzzle);

extern void PuzzleMakeGuess(Puzzle* puzzle, const char* guess, Result* result);

extern int PuzzleGameIsOver(Puzzle* puzzle);

#endif