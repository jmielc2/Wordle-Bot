from abc import ABC, abstractmethod

class WordValueEvaluator(ABC):

    @abstractmethod
    def evaluate_word(word):
        pass