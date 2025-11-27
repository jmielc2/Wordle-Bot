from wordle_puzzle import WordlePuzzle
from word_bank import WordBank
from word_value_evaluator import EntropyEvaluator
from util import Result
import copy

YELLOW_BLOCK_CODE = "\U0001F7E8"
GRAY_BLOCK_CODE = "\U00002B1B"
GREEN_BLOCK_CODE = "\U0001F7E9"
RESULT_TO_UNICODE = {
    Result.GRAY : GRAY_BLOCK_CODE,
    Result.YELLOW : YELLOW_BLOCK_CODE,
    Result.GREEN : GREEN_BLOCK_CODE
}

class WordleBot:
    _SORTER = lambda item: item[1]

    def __init__(self, wb: WordBank, evaluator: EntropyEvaluator):
        print("Initializing wordle bot...")
        self._wb = wb
        self._puzzle = None
        tuple_list = [(word, evaluator.evaluate_word(word, None, wb)) for word in wb.words]
        tuple_list.sort(key=WordleBot._SORTER)
        self._firstGuess = tuple_list[-1][0]
        self._evaluator = evaluator

    def _printResult(result: int):
        v = result
        for i in range(5):
            r = v % 3
            print(RESULT_TO_UNICODE[r], end = "")
            v -= r
            v /= 3

    def setPuzzle(self, puzzle: WordlePuzzle):
        self._puzzle = puzzle
        
    def solve(self, verbose = True) -> tuple:
        puzzle = self._puzzle
        wb = copy.deepcopy(self._wb)
        evaluator = self._evaluator

        while not puzzle.isWon and puzzle.numGuesses < 6:
            guess = self._firstGuess
            if puzzle.numGuesses > 0:
                tuple_list = [(word, evaluator.evaluate_word(word, puzzle, wb)) for word in wb.words]
                tuple_list.sort(key=WordleBot._SORTER)
                guess = tuple_list[-1][0]
            result = puzzle.makeGuess(guess)
            wb = wb.refineWordBank(guess, result)
            if verbose:
                WordleBot._printResult(result)
                print(f" -> {guess}")
        
        if puzzle.isWon:
            print(f"Hooray, wordle bot guessed {puzzle.lastGuess} in {puzzle.numGuesses} tries!\n")
        else:
            print(f"Oh no! Wordle bot didn't guess {puzzle.word} within 6 tries :(\n")
        return puzzle.isWon, puzzle.numGuesses