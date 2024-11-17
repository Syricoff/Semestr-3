class Student:
    x = 0
    y = 0
    z = 0
    group = "ИУК4-32Б"

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def amount_of_homework(self):
        res = self.x + self.y + self.z
        return res

    def print_amount_of_student(self):
        print("Необходимо выполнить:", self.amount_of_homework(), "домашних заданий.")

    def print_group(self):
        print("Группа:", self.group)


class Kate(Student):
    pass


class Peter(Student):
    def __init__(self, x, y):
        super().__init__(x, y, z=None)

    def amount_of_homework(self):
        res = self.x + self.y
        return res


math_k = int(input("Количество заданий по математике для Kate: "))
language_k = int(input("Количество заданий по английскому для Kate: "))
literature_k = int(input("Количество заданий по литературе для Kate: "))
kate = Kate(math_k, language_k, literature_k)

math_p = int(input("\nКоличество заданий по математике для Peter: "))
language_p = int(input("Количество заданий по английскому для Peter: "))
peter = Peter(math_p, language_p)

print("Kate")
kate.print_group()
kate.print_amount_of_student()

print("\nPeter")
peter.print_group()
peter.print_amount_of_student()

