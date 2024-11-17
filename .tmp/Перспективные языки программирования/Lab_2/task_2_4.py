from faker import Faker
import random as rand

fake = Faker('ru_RU')
students = [(fake.unique.first_name(), rand.randint(18, 24), fake.phone_number()) for i in range(5)]
print(*students, sep='\n')
names = [i[0] for i in students]
numbers = [i[2] for i in students]
print(f"Список имен: {names}")
print(f"Список номеров: {numbers}")
