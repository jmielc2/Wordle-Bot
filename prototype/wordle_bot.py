from wordle_puzzle import WordlePuzzle
from word_bank import WordBank
from word_value_evaluator import WordValueEvaluator
from wordle_puzzle import Result
import copy

YELLOW_BLOCK_CODE = "\U0001F7E8"
GRAY_BLOCK_CODE = "\U00002B1B"
GREEN_BLOCK_CODE = "\U0001F7E9"

class WordleBot:
    def _sorter(a):
        return a[1]

    def __init__(self, wb: WordBank, evaluator: WordValueEvaluator):
        self._wb = wb
        self._puzzle = None
        tuple_list = [(word, evaluator.evaluate_word(word, wb)) for word in wb.words]
        tuple_list.sort(key=WordleBot._sorter)
        self._firstGuess = tuple_list[-1][0]
        self._evaluator = evaluator

    def _printResult(results: list):
        for result in results:
            if result == Result.GREEN:
                print(GREEN_BLOCK_CODE, end = "")
            elif result == Result.YELLOW:
                print(YELLOW_BLOCK_CODE, end = "")
            elif result == Result.GRAY:
                print(GRAY_BLOCK_CODE, end = "")
            else:
                raise RuntimeError("Invalid argument. Result must contain only green, yellow, or gray values.")

    def setPuzzle(self, puzzle: WordlePuzzle):
        self._puzzle = puzzle
        
    def solve(self, verbose = True) -> tuple:
        puzzle = self._puzzle
        wb = copy.deepcopy(self._wb)
        evaluator = self._evaluator

        while (not puzzle.isWon and puzzle.numGuesses < 6):
            guess = self._firstGuess
            if (puzzle.numGuesses > 0):
                tuple_list = [(word, evaluator.evaluate_word(word, wb)) for word in wb.words]
                tuple_list.sort(key=WordleBot._sorter)
                guess = tuple_list[-1][0]
            results = puzzle.makeGuess(guess)
            wb = wb.refineWordBank(guess, results)
            if (verbose):
                WordleBot._printResult(results)
                print(f" -> {guess}")
        
        if (puzzle.isWon):
            print(f"Hooray, wordle bot guessed {puzzle.lastGuess} in {puzzle.numGuesses} tries!\n")
        else:
            print(f"Oh no! Wordle bot didn't guess {puzzle.word} within 6 tries :(\n")
        return (puzzle.isWon, puzzle.numGuesses)