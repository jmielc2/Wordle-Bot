from count_matrix import CountMatrix

class WordBank:

    def __init__(self, filename, words = None):
        if not words:
            self.loadWordBank(filename)
        else:
            self.loadWordBank(filename, words = words)

    def __isIndexInBounds(self, i):
        return i >= 0 and i < self.size

    @property
    def size(self):
        return len(self._words)
    
    @property
    def words(self):
        return self._words

    def loadWordBank(self, filename, words = None):
        if not words:
            self.resetWordBank()
            file = open(filename)
            self._words = [word.strip() for word in file.read().split() if word.strip()]
        else:
            self._words = words

    def resetWordBank(self):
        self._words = []
        self._index = 0
    
    def getWord(self, i = -1):
        i = int(i)
        i = self._index if i == -1 else i
        if self.size == 0:
            raise RuntimeError("Word bank is empty.")
        if (not self.__isIndexInBounds(i)):
            raise IndexError("Index out of world bank bounds.")
        return self._words[i]
    
    def generateCountMatrix(self):
        return CountMatrix(self)

    def refineWordBank(self, guess, result):
        pass