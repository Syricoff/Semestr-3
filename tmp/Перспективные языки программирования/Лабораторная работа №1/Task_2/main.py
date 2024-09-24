import random

N = 178
X = [random.randint(-100, 100) for i in range(N)]
print(X)
print("Максимальное значение:", max(X))
print("Минимальное значение:", min(X))
print("Ответ:", abs(max(X) - min(X)))
