from employee import Employee
from visitor import Visitor


def main():
    people_in_store = [
        Employee("Иванов Иван Иванович", "Менеджер"),
        Visitor("Петрова Анна Сергеевна", 30),
        Employee("Сидоров Алексей Владимирович", "Кассир"),
        Visitor("Кузнецова Мария Петровна", 25),
    ]

    for person in people_in_store:
        print(person.display_info())


if __name__ == "__main__":
    main()
