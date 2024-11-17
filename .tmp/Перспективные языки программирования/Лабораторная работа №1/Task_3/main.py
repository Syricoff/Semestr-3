str = input("Введите строку: ")
if str == ''.join(sorted(str, reverse=True)):
    print("Да")
else:
    print("Нет")
