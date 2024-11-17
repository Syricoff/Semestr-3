import re

string = input("Введите строку: ")
string = ' ' + string.replace(' ', '  ') + ' '
pattern = re.compile('\s([a-zA-Z][a-zA-Z0-9]+)\s')
words = re.findall(pattern, string)
print(' '.join(words))
print("Количество слов:", len(words))

input()
