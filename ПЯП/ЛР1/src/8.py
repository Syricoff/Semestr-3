import math


def f(x) -> float:
    return math.sin(x) + math.sin(2 * x**2) + math.sin(3 * x**3)


x = 0.0
while x <= 1.2:
    print(f"f({x:.1f}) = {f(x):.4f}")
    x += 0.1
