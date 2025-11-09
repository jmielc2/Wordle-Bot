from word_value_evaluator import WordValueEvaluator
from word_bank import WordBank
from wordle_puzzle import WordlePuzzle, Result
import string, copy

UNKNOWN = 0
NOT_IN_WORD = 1
IN_WORD = 2
IN_POSITION = 3
INIT_PUZZLE_DATA = {letter: (UNKNOWN, [0, 1, 2, 3, 4]) for letter in string.ascii_lowercase}

class ITEvaluator(WordValueEvaluator):

    def getPossibleResults(word: str, puzzle: WordlePuzzle) -> dict:
        puzzleData = copy.deepcopy(INIT_PUZZLE_DATA)
        if (puzzle == None):
            return puzzleData
        for guess, results in puzzle.guessHistory:
            for i, result in enumerate(results):
                letter = guess[i]
                if result == Result.GRAY:
                    puzzleData[letter] = (NOT_IN_WORD, [])
                elif result == Result.YELLOW:
                    puzzleData[letter][1].remove(i)
                    if (len(puzzleData[letter][1]) == 1):
                        puzzleData[letter] = (IN_POSITION, puzzleData[letter][1])
                    else:
                        puzzleData[letter] = (IN_WORD, puzzleData[letter][1])
                elif result == Result.GREEN:
                    puzzleData[letter] = (IN_POSITION, [i])
                else:
                    raise RuntimeError("Invalid puzzle result")
        return puzzleData
    
    def evaluate_word(word: str, wb: WordBank) -> float:
        results = ITEvaluator.getPossibleResults(word, None)
        return 0