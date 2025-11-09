from word_bank import WordBank
from wordle_puzzle import WordlePuzzle
from wordle_bot import WordleBot
from naive_evaluator import NaiveEvaluator
from it_evaluator import ITEvaluator
import random

def selectRandomWord(words: list) -> str:
    return words[int(random.random() * len(words))]

if __name__ == "__main__":
    wb = WordBank("../words/wordle_words.txt")
    puzzle = WordlePuzzle("among")
    bot = WordleBot(wb, NaiveEvaluator)
    # bot = WordleBot(wb, ITEvaluator)

    numGuesses = 0
    numFailed = 0
    failedWords = []
    numPuzzles = wb.size
    print(f"Trialing {numPuzzles} Puzzles...\n")
    for i in range(numPuzzles):
        word = wb.words[i]
        # word = selectRandomWord(wb.words)
        puzzle.resetPuzzle(word)
        bot.setPuzzle(puzzle)
        print(f"Puzzle {i}: {word.upper()}")
        results = bot.solve(verbose = True)
        if not results[0]:
            numFailed += 1
            failedWords.append(word)
        numGuesses += results[1]
    
    print("=== WORDLE BOT DATA ===")
    print(f"Average Number of Guesses: {numGuesses / numPuzzles}")
    print(f"Num Failed Puzzles: {numFailed}")
    for word in failedWords:
        print(f" - {word}")
    print()