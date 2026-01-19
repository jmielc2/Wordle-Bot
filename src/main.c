#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "word_bank.h"
#include "puzzle.h"

int main(void) {
    WB wb;
    if (!InitWordBank("../words/wordle_words.txt", &wb)) {
        printf("Failed to initialize Word Bank.\n");
        return 1;
    }
    Cursor cursor;
    CreateWordBankCursor(&wb, &cursor);

    // Test 1
    /*
    srand(time(NULL));
    const int wordIndex = rand() % wb.total_word_count;

    Puzzle puzzle;
    MoveToIndex(&cursor, wordIndex);
    InitPuzzle(&puzzle, GetWord(&cursor));

    int i = wordIndex - 4;
    Result result;
    while (!PuzzleGameIsOver(&puzzle)) {
        MoveToIndex(&cursor, i);
        PuzzleMakeGuess(&puzzle, GetWord(&cursor), &result);
        if (PuzzleGameIsWon(&puzzle)) {
            printf("Puzzle solved in %i guesses. Answer: %s\n", puzzle.num_guesses, PuzzleGetLastGuess(&puzzle));
        }
        i++;
    }
    if (!PuzzleGameIsWon(&puzzle)) {
        printf("Puzzle not solved. Word was '%s'.", puzzle.word);
    }
    printf("Guess History:\n");
    for (i = 0; i < puzzle.num_guesses; i++) {
        printf(" - %s\n", PuzzleGetGuess(&puzzle, i));
    }
    */

    // Test 2
    Result result;
    EvaluateResult(&result, "aback", "agape");
    WB new_wb;
    Cursor new_cursor;
    RefineWordBank(&wb, "aback", &result, &new_wb);
    CreateWordBankCursor(&new_wb, &new_cursor);
    printf("Refined Word Bank:\n");
    while (new_cursor.wb_index < new_wb.total_word_count) {
        printf(" - %s\n", GetWord(&new_cursor));
        MoveToNextWord(&new_cursor);
    }
    DestroyWordBankCursor(&new_cursor);
    DestroyWordBank(&new_wb);

    DestroyWordBankCursor(&cursor);
    DestroyWordBank(&wb);
    return 0;
}