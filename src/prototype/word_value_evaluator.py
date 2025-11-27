from abc import ABC, abstractmethod
from word_bank import WordBank
from wordle_puzzle import WordlePuzzle

class EntropyEvaluator(ABC):
    
    @abstractmethod
    def evaluate_word(word: str, puzzle: WordlePuzzle, wb: WordBank) -> float:
        pass