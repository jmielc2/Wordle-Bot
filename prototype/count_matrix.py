import string, copy

class CountMatrix:

    def __init__(self, wb):
        self._word_bank = wb
        self.__initMatrix()
        for word in self._word_bank.words:
            for i, letter in enumerate(word):
                self._countMatrix[letter.lower()][i] += 1


    def __initMatrix(self):
        initialProbabilities = [0 for _ in range(5)]
        self._countMatrix = {letter: copy.deepcopy(initialProbabilities) for letter in string.ascii_lowercase}

    @property
    def countMatrix(self):
        return self._countMatrix

    def getProbability(self, letter, index):
        return self._countMatrix[letter][index] / self._word_bank.size

    def numWordsEliminated(self, letter, i):
        gray_value = 0.0
        yellow_value = 0.0
        green_value = self._word_bank.size - self._countMatrix[letter][i]
        for word in self._word_bank.words:
            letter_in_word = letter in word
            if letter_in_word:
                gray_value += 1
            if not letter_in_word or word[i] == letter:
                yellow_value += 1
        return gray_value, yellow_value, green_value