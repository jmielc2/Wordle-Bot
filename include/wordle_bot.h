//
// Created by jacob on 1/19/2026.
//

#ifndef WORDLE_BOT_H
#define WORDLE_BOT_H

#include "puzzle.h"
#include "word_bank.h"

typedef struct {
    WB* wb;
    char first_guess[WORD_LEN];
} WordleBot;

void InitWordleBot(WordleBot* bot, WB* wb);

void WordleBotSolvePuzzle(WordleBot* bot, Puzzle* puzzle);

#endif
