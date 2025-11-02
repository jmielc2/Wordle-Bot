YELLOW_BLOCK_CODE = "\U0001F7E8"
GRAY_BLOCK_CODE = "\U00002B1B"
GREEN_BLOCK_CODE = "\U0001F7E9"

class WordlePuzzle:

    def __init__(self, word):
        self._word = word
        self.resetPuzzle()

    def resetPuzzle(self):
        self.guessHistory = []

    def makeGuess(self, guess):
        self.guessHistory.append(guess)