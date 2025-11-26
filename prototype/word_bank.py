from count_matrix import CountMatrix
from wordle_puzzle import Result
from typing import Optional

class WordBank:

    def __init__(self, filename: Optional[str], words: list = None):
        self._index = 0
        self._words = None
        if not words:
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
        if not words:
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

    def refineWordBank(self, guess: str, results: list):
        refined_words = []
        for word in self._words:
            valid = True
            for i, result in enumerate(results):
                if result == Result.GREEN:
                    valid = guess[i] == word[i]
                elif result == Result.YELLOW:
                    valid = guess[i] in word and not guess[i] == word[i]
                elif result == Result.GRAY:
                    valid = guess[i] not in word
                if not valid:
                    break
            if valid:
                refined_words.append(word)
        return WordBank(filename = None, words = refined_words)

    def getResultCounts(self, guess: str) -> list:
        results = [0 for _ in range(pow(3, 5))]
        for word in self._words:
            result = 0
            for i, letter in enumerate(guess):
                if letter == word[i]:
                    a = Result.GREEN
                elif letter in word:
                    a = Result.YELLOW
                else:
                    a = Result.GRAY
                result += pow(3, i) * a
            results[result] += 1
        return results
