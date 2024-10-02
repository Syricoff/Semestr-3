from person import Person


class Visitor(Person):
    def __init__(self, full_name, age):
        super().__init__(full_name)
        self.age = age

    def display_info(self):
        return f"Посетитель: {self.full_name}, Возраст: {self.age}"
