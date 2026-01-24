//
// Created by jacob on 1/19/2026.
//

#ifndef WORDLE_BOT_H
#define WORDLE_BOT_H

#include "puzzle.h"
#include "word_bank.h"

typedef struct {
    WB* wb;
    WB _wb_working_copy;
    char first_guess[WORD_LEN];
    char next_guess[WORD_LEN];
} WordleBot;

extern void InitWordleBot(WordleBot* bot, WB* wb);

extern void WordleBotSolvePuzzle(WordleBot* bot, Puzzle* puzzle);

#endif
