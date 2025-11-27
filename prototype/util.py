class Result:
    GRAY = 0
    YELLOW = 1
    GREEN = 2

def EvaluateResult(a: str, b: str) -> list:
    result = [Result.GRAY for _ in range(5)]
    word = list(b)
    guess = list(a)
    for i, letter in enumerate(guess):
        if letter == word[i]:
            word[i] = None
            guess[i] = None
            result[i] = Result.GREEN
    for i, letter in enumerate(guess):
        if letter is not None and letter in word:
            result[i] = Result.YELLOW
            j = word.index(letter)
            word[j] = None
    return result


def EvaluateResultAsInt(a: str, b: str) -> int:
    results = EvaluateResult(a, b)
    base = 1
    result = 0
    for r in results:
        result += base * r
        base *= 3
    return result