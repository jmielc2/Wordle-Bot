#include "puzzle.h"
#include "util.h"
#include <stdio.h>

static void PuzzleAddGuessHistoryEntry(Puzzle* puzzle, const Result* result, const char* guess) {
    GuessHistoryEntry* entry = &puzzle->_guesses[puzzle->num_guesses];
    memcpy(&entry->result, result, sizeof(Result));
    memcpy(entry->guess, guess, WORD_LEN);
    puzzle->num_guesses++;
}

void InitPuzzle(Puzzle* puzzle, const char* word) {
    ResetPuzzle(puzzle, word);
}

void ResetPuzzle(Puzzle* puzzle, const char* word) {
    if (word != NULL) {
        memcpy(&puzzle->word, word, WORD_LEN);
    } else {
        memset(&puzzle->word, '\0', WORD_LEN);
    }
    memset(puzzle->_guesses, 0, sizeof(puzzle->_guesses));
    puzzle->num_guesses = 0;
}

char* PuzzleGetGuess(Puzzle* puzzle, int index) {
    if (index < 0 || index >= puzzle->num_guesses) {
        fprintf(stderr, "Puzzle guess index out of range.\n");
        return NULL;
    }
    return puzzle->_guesses[index].guess;
}

char* PuzzleGetLastGuess(Puzzle* puzzle) {
    if (puzzle->num_guesses == 0) {
        fprintf(stderr, "Puzzle has no guess history.\n");
        return "\0";
    }
    return PuzzleGetGuess(puzzle, puzzle->num_guesses - 1);
}

int PuzzleGameIsWon(Puzzle* puzzle) {
    if (puzzle->num_guesses > 0 && puzzle->num_guesses <= NUM_GUESSES && !strcmp(puzzle->word, PuzzleGetLastGuess(puzzle))) {
        return 1;
    }
    return 0;
}

void PuzzleMakeGuess(Puzzle* puzzle, const char* guess, Result* result) {
    if (puzzle->num_guesses == 6) {
        fprintf(stderr, "Game over. You only have %i guesses.\n", NUM_GUESSES);
        return;
    }
    EvaluateResult(result, guess, puzzle->word);
    PuzzleAddGuessHistoryEntry(puzzle, result, guess);
}

int PuzzleGameIsOver(Puzzle* puzzle) {
    return puzzle->num_guesses >= NUM_GUESSES || PuzzleGameIsWon(puzzle);
}