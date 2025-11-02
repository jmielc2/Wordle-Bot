from abc import ABC, abstractmethod
from count_matrix import CountMatrix

class WordValueEvaluator(ABC):
    
    @abstractmethod
    def evaluate_word(word: str, count_matrix: CountMatrix) -> float:
        pass