from word_value_evaluator import WordValueEvaluator
from word_bank import WordBank
from wordle_puzzle import WordlePuzzle
import math

class ITEvaluator(WordValueEvaluator):

    def evaluate_word(word: str, puzzle: WordlePuzzle, wb: WordBank) -> float:
        sum = 0
        for count in wb.getResultCounts(word):
            p = count / wb.size
            if p > 0:
                sum += -math.log2(p) * p
        return sum