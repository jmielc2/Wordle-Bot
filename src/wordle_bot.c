//
// Created by jacob on 1/19/2026.
//

#include "wordle_bot.h"

#include <stdio.h>

static char* RESULT_TO_UNICODE[3] = { "\U00002B1B", "\U0001F7E8", "\U0001F7E9"};

static void PrintResult(int result) {
    int v = result;
    for (int i = 0; i < 5; i++) {
        int r = v % 3;
        printf("%s", RESULT_TO_UNICODE[r]);
        v -= r;
        v /= 3;
    }
}

static char* EvaluateNextGuess(WB* wb) {
    return "\0";
}

void InitWordleBot(WordleBot* bot, WB* wb) {
    bot->wb = wb;
    strcpy(bot->first_guess, EvaluateNextGuess(bot->wb));
}

void WordleBotSolvePuzzle(WordleBot* bot, Puzzle* puzzle) {

}