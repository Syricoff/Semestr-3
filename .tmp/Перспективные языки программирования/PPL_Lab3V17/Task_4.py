from abc import ABC


class Person(ABC):
    name = ''
    surname = ''
    third_name = ''

    def __init__(self, name, surname, third_name):
        self.name = name
        self.surname = surname
        self.third_name = third_name

    def print_info(self):
        print("Имя:", self.name)
        print("Фамилия:", self.surname)
        print("Отчество:", self.third_name)


class Worker(Person):
    position = ''

    def __init__(self, name, surname, third_name, position):
        super().__init__(name, surname, third_name)
        self.position = position

    def print_info(self):
        print("Фамилия:", self.surname)
        print("Должность:", self.position)


class Visitor(Person):
    age = 0

    def __init__(self, name, surname, third_name, age):
        super().__init__(name, surname, third_name)
        self.age = age

    def print_info(self):
        print("Имя:", self.name)
        print("Возраст:", self.age)


persons = [Visitor("Даниил", "Зудин", "Васильевич", 19), Worker("Михаил", "Чузов", "Юрьевич", "Кассир")]
for person in persons:
    person.print_info()
    print()
