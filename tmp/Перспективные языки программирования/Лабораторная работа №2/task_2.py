import random as rand

#Создание рандомного файла 
with open("task_2.txt", "w") as file:
	for k in range(rand.randint(20,40)):
		string = []
		for i in range(rand.randint(10, 20)):
			word = ''
			for j in range(rand.randint(5, 10)):
				word += chr(rand.randint(ord('a'), ord('z')))
			string.append(word)
		file.write(' '.join(string) + '\n')

inp = input("Введите строку: ")
content = []
with open("task_2.txt", "r") as file:
	content = file.readlines()
print(content)

input()
