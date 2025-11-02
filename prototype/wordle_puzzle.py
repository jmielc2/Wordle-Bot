class Result:    
    GRAY = 0
    YELLOW = 1
    GREEN = 2

class WordlePuzzle:

    def __init__(self, word: str):
        self.resetPuzzle(word)

    def resetPuzzle(self, word: str = None):
        if (word):
            self._word = word
        self._guessHistory = []

    @property
    def word(self) -> str:
        return self._word

    @property
    def numGuesses(self) -> int:
        return len(self._guessHistory)
    
    @property
    def lastGuess(self) -> str:
        if (self.numGuesses == 0):
            raise RuntimeError("Can't get last guess. No guesses made.")
        return self._guessHistory[-1]
    
    @property
    def isWon(self) -> bool:
        if self.numGuesses == 0:
            return False
        return self._guessHistory[-1] == self._word

    def makeGuess(self, guess: str) -> list:
        if self.numGuesses == 6:
            raise RuntimeError("Game over. You have only 6 guesses.")
        self._guessHistory.append(guess)
        results = []
        for i, letter in enumerate(guess):
            if (self._word[i] == letter):
                results.append(Result.GREEN)
            elif (letter in self._word):
                results.append(Result.YELLOW)
            else:
                results.append(Result.GRAY)
        return results