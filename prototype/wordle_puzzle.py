from util import EvaluateResultAsInt

class WordlePuzzle:

    def __init__(self, word: str):
        self.resetPuzzle(word)

    def resetPuzzle(self, word: str = None):
        if word:
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
        if self.numGuesses == 0:
            raise RuntimeError("Can't get last guess. No guesses made.")
        return self._guessHistory[-1][0]

    @property
    def guessHistory(self) -> list:
        return self._guessHistory
    
    @property
    def isWon(self) -> bool:
        if self.numGuesses == 0:
            return False
        return self._guessHistory[-1][0] == self._word

    def makeGuess(self, guess: str) -> int:
        if self.numGuesses == 6:
            raise RuntimeError("Game over. You have only 6 guesses.")
        result = EvaluateResultAsInt(guess, self.word)
        self._guessHistory.append((guess, result))
        return result