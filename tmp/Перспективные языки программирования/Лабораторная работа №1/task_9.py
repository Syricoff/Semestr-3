def func(n):
	a = (-1) ** n 
	s = sum(1 / i for i in range(1, n + 1))
	return a * s 

a = float(input("Введите число А: "))
b = float(input("Введите число B: "))
cnt = 1
x = func(cnt)
while a <= x <= b:
	cnt += 1
	x = func(cnt)
print(f"Результат: {x}")
input()
