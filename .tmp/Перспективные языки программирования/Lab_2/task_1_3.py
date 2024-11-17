import random as rand
from faker import Faker

fake = Faker("ru_RU")
# Создание рандомного файла
with open("task_1_3.txt", "w") as file:
    for i in range(rand.randint(20, 40)):
        string = []
        name = fake.unique.first_name() + ';'
        number = fake.phone_number()
        string.append(name)
        string.append(number)
        file.write(' '.join(string) + '\n')

# Считывание файла
content = ""
with open("task_1_3.txt", "r") as file:
    content = ' '.join(file.readlines())
    content = content.split('\n')[:-1]
    content = [x.split(';') for x in content]
    print(content)

# Составление словаря
d = {x.strip(): y.strip() for x, y in content}
print(d)

