x = float(input("Введите число х: "))
y, a = 1, x
while abs(y - a) >= 10 ** -5:
	a = y
	y = 1 / 3 * (2 * a + x / a ** 2)
print(f"Результат: {round(y, 2)}")

input()
