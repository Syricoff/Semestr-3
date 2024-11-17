inp = input("Введите строку: ")
res = 0
for i in inp:
	if i.isdigit():
		res += int(i)
if res == len(inp):
	print("Сумма чисел равна длине строки")
else:
	print("Сумма чисел НЕ равна длине строки")
input()
