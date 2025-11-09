from word_bank import WordBank
from word_value_evaluator import WordValueEvaluator

class NaiveEvaluator(WordValueEvaluator):

    def evaluate_word(word: str, wb: WordBank) -> float:
        value = 0.0
        count_matrix = wb.generateCountMatrix()
        for i, letter in enumerate(word):
            p = count_matrix.getProbability(letter, i)
            (gray, yellow, green) = count_matrix.numWordsEliminated(letter, i)
            value += p * (gray + yellow + green)
        return value