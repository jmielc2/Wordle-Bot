class WordBank:

    def __init__(self, filename):
        self.loadWordBank(filename)

    def __init(self):
        self.resetWordBank()

    def __isIndexInBounds(self, i):
        return i >= 0 and i < self.size

    @property
    def size(self):
        return len(self._words)
    
    @property
    def index(self):
        return self._index

    def loadWordBank(self, filename):
        self.resetWordBank()
        file = open(filename)
        self._words = [word.strip() for word in file.read().split() if word.strip()]

    def resetWordBank(self):
        self._words = []
        self._index = 0
    
    def getWord(self, i = -1):
        i = int(i)
        i = self._index if i == -1 else i
        if (self.size == 0):
            raise RuntimeError("Word bank is empty. No word to read")
        if (not self.__isIndexInBounds(i)):
            raise IndexError("Index out of world bank bounds")
        return self._words[i]
    
    def next(self):
        self._index += 1
        if (self.size == self._index):
            self._index = 0
        return self.getWord()
    
    def prev(self):
        self._index -= 1
        if (0 > self._index):
            self._index = self.size - 1
        return self.getWord()
    
    def setIndex(self, i):
        i = int(i)
        if (self.size == 0):
            raise RuntimeError("Word bank is empty. No word to read")
        if (not self.__isIndexInBounds(i)):
            raise IndexError("Index out of world bank bounds")
        self._index = i