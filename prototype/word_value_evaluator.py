from abc import ABC, abstractmethod
from word_bank import WordBank

class WordValueEvaluator(ABC):
    
    @abstractmethod
    def evaluate_word(word: str, wb: WordBank) -> float:
        pass