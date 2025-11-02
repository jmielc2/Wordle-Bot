from count_matrix import CountMatrix
from word_value_evaluator import WordValueEvaluator

class MyEvaluator(WordValueEvaluator):

    def evaluate_word(word: str, count_matrix: CountMatrix) -> float:
        value = 0.0
        for i, letter in enumerate(word):
            p = count_matrix.getProbability(letter, i)
            (gray, yellow, green) = count_matrix.numWordsEliminated(letter, i)
            value += p * (gray + yellow + green)
        return value