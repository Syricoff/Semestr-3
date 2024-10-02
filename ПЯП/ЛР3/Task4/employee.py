from person import Person


class Employee(Person):
    def __init__(self, full_name, position):
        super().__init__(full_name)
        self.position = position

    def display_info(self):
        last_name = self.full_name.split()[-1]
        return f"Сотрудник: {last_name}, Должность: {self.position}"
