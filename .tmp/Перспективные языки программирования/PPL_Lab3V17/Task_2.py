from abc import ABC, abstractmethod


class Convert(ABC):
    @abstractmethod
    def convert(self, value):
        pass


class Bin(Convert):
    def convert(self, value):
        res = ''
        while value > 0:
            res += str(value % 2)
            value //= 2
        return res


a = int(input("Введите число: "))
print("Число", a, "в двочной системе счисления:", Bin().convert(a))
