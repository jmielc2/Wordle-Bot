from word_bank import WordBank
from my_evaluator import MyEvaluator
from it_evaluator import ITEvaluator
import pprint as pp

def sorter(a):
    return a[1]

if __name__ == "__main__":
    wb = WordBank("../words/wordle_words.txt")
    cMatrix = wb.generateCountMatrix()

    tuple_list = [(word, MyEvaluator.evaluate_word(word, cMatrix)) for word in wb.words]
    tuple_list.sort(key=sorter)

    pp.pprint(tuple_list)