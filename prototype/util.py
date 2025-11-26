class Result:
    GRAY = 0
    YELLOW = 1
    GREEN = 2

def EvaluateResult(a: str, b: str) -> list:
    result = [Result.GRAY for _ in range(5)]
    word = list(b)
    for i, letter in enumerate(a):
        if letter == word[i]:
            word[i] = None
            result[i] = Result.GREEN
    for i, letter in enumerate(a):
        if letter in word:
            i = word.index(letter)
            word[i] = None
            result[i] = Result.YELLOW
    return result


def EvaluateResultAsInt(a: str, b: str) -> int:
    results = EvaluateResult(a, b)
    base = 1
    result = 0
    for r in results:
        result += base * r
        base *= 3
    return result