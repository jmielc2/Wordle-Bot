from word_value_evaluator import WordValueEvaluator
from word_bank import WordBank
from wordle_puzzle import WordlePuzzle, Result
import math

# UNKNOWN = 0
# NOT_IN_WORD = 1
# IN_WORD = 2
# IN_POSITION = 3
POSSIBLE_RESULTS = [[int(i / 81) % 3, int(i / 27) % 3, int(i / 9) % 3, int(i / 3) % 3, i % 3] for i in range(pow(3, 5))]

class ITEvaluator(WordValueEvaluator):

    def evaluate_word(word: str, puzzle: WordlePuzzle, wb: WordBank) -> float:
        sum = 0
        for result in POSSIBLE_RESULTS:
            p = wb.wordResultProbability(word, result)
            if p == 0:
                continue
            sum += math.log2(p) * p
        # print(f"processed {word}...")
        return -sum