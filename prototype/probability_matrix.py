import string, copy

class ProbabilityMatrix:

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