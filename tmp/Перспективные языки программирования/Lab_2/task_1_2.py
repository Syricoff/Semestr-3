import random as rand

# Создание рандомного файла
with open("task_1_2.txt", "w") as file:
	for k in range(rand.randint(20, 40)):
		string = []
		for i in range(rand.randint(10, 20)):
			word = ''
			for j in range(rand.randint(5, 10)):
				word += chr(rand.randint(ord('a'), ord('z')))
			string.append(word)
		file.write(' '.join(string) + '\n')

# Считывание файла
content = ""
with open("task_1_2.txt", "r") as file:
	content = ' '.join(file.readlines())
	content.split(" ")
print(*content, sep='')

# Поиск подстроки в итоговой строке
inp = input("Введите строку: ")
res = [i for i in content.split() if i.startswith(inp)]
print(*res)



