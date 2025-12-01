from word_bank import WordBank
from wordle_puzzle import WordlePuzzle
from wordle_bot import WordleBot
from naive_evaluator import NaiveEvaluator
from it_evaluator import ITEvaluator
import random, sys

def selectRandomWord(words: list) -> str:
    return words[int(random.random() * len(words))]

if __name__ == "__main__":
    file = "../../words/wordle_words.txt"
    if len(sys.argv) == 2:
        file = sys.argv[1]
    elif len(sys.argv) > 2:
        print("Usage: python main.py [word/bank/file/path.txt]")
        exit(1)

    wb = WordBank(file)
    puzzle = WordlePuzzle()
    # bot = WordleBot(wb, NaiveEvaluator)
    bot = WordleBot(wb, ITEvaluator)

    numGuesses = 0
    failedWords = []
    numPuzzles = wb.size
    print(f"Trialing {numPuzzles} Puzzles...\n")
    for i in range(numPuzzles):
        word = wb.words[i]
        # word = selectRandomWord(wb.words)
        puzzle.resetPuzzle(word)
        bot.setPuzzle(puzzle)
        print(f"Puzzle {i}: {word.upper()}")
        result = bot.solve(verbose = True)
        if not result[0]:
            failedWords.append(word)
        numGuesses += result[1]
    
    print("=== WORDLE BOT DATA ===")
    print(f"Average Number of Guesses: {numGuesses / numPuzzles}")
    print(f"Number of Failed Puzzles: {len(failedWords)}")
    print(f"Failed Puzzles: {failedWords}")