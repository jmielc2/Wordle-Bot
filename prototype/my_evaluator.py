class MyEvaluator:

    def evaluate_word(word, count_matrix):
        value = 0.0
        for i, letter in enumerate(word):
            p = count_matrix.getProbability(letter, i)
            (gray, yellow, green) = count_matrix.numWordsEliminated(letter, i)
            value += p * (gray + yellow + green)
        return value