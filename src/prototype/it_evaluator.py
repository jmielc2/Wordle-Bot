from word_value_evaluator import EntropyEvaluator
from word_bank import WordBank
from wordle_puzzle import WordlePuzzle
import math

class ITEvaluator(EntropyEvaluator):

    def evaluate_word(word: str, puzzle: WordlePuzzle, wb: WordBank) -> float:
        sum = 0
        validCount = 0
        for count in wb.getResultCounts(word):
            p = count / wb.size
            if p > 0:
                validCount += 1
                sum += -math.log2(p) * p
        return sum * validCount / wb.size