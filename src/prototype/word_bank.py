from count_matrix import CountMatrix
from util import EvaluateResultAsInt
from typing import Optional

class WordBank:

    def __init__(self, filename: Optional[str], words: list = None):
        self._index = 0
        self._words = None
        if words is None:
            self.loadWordBank(filename)
        else:
            self.loadWordBank(filename, words = words)

    def _isIndexInBounds(self, i):
        return 0 <= i < self.size

    @property
    def size(self) -> int:
        return len(self._words)
    
    @property
    def words(self):
        return self._words

    def loadWordBank(self, filename: str, words: list = None):
        if words is None:
            self.resetWordBank()
            file = open(filename)
            self._words = [word.strip() for word in file.read().split() if word.strip()]
        else:
            self._words = words

    def resetWordBank(self):
        self._words = []
        self._index = 0
    
    def getWord(self, i: int = -1) -> str:
        i = int(i)
        i = self._index if i == -1 else i
        if self.size == 0:
            raise RuntimeError("Word bank is empty.")
        if not self._isIndexInBounds(i):
            raise IndexError("Index out of world bank bounds.")
        return self._words[i]
    
    def generateCountMatrix(self) -> CountMatrix:
        return CountMatrix(self)

    def refineWordBank(self, guess: str, results: int):
        refined_words = []
        for word in self._words:
            wordResult = EvaluateResultAsInt(guess, word)
            if wordResult == results:
                refined_words.append(word)
        return WordBank(filename = None, words = refined_words)

    def getResultCounts(self, guess: str) -> list:
        results = [0 for _ in range(pow(3, 5))]
        for word in self._words:
            result = EvaluateResultAsInt(guess, word)
            results[result] += 1
        return results
