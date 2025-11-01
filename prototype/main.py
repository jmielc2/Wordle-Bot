from word_bank import WordBank
from probability_matrix import ProbabilityMatrix
import pprint as pp

wb = WordBank("../words/wordle_words.txt")

pMatrix = ProbabilityMatrix(wb)
pp.pprint(pMatrix.countMatrix)
