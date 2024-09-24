class Shopper:
    def __init__(self):
        """Инициализация покупателя"""
        self.__shopper_id = 0               # ID
        self.__name = ''                    # ФИО
        self.__date_of_birthday = ''        # Дата рождения
        self.__total = 0                    # Общая сумма покупок
        self.__orders = 0                   # Количество заказов

    def __str__(self):
        """Форматирование вывода информации о покупателе"""
        return f"ID: {self.__shopper_id}\n" \
               f"ФИО: {self.__name}\n" \
               f"Дата рождения: {self.__date_of_birthday}\n" \
               f"Общая сумма покупок: {self.__total} р.\n"\
               f"Количество заказов: {self.__orders} шт."

    @property
    def shopper_id(self):
        return self.__shopper_id

    @shopper_id.setter
    def shopper_id(self, shopper_id: int):
        if shopper_id > 0:
            self.__shopper_id = shopper_id
        else:
            raise ValueError("Incorrect input!")

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name: str):
        self.__name = name

    @property
    def date_of_birthday(self):
        return self.__date_of_birthday

    @date_of_birthday.setter
    def date_of_birthday(self, date_of_birthday: str):
        valid = True
        if len(date_of_birthday) != 10 and date_of_birthday[2] != '.' and date_of_birthday[5] != '.':
            valid = False
        if not 0 < int(date_of_birthday[:2]) < 32:
            valid = False
        if not 0 < int(date_of_birthday[3:5]) < 13:
            valid = False
        if not 1900 < int(date_of_birthday[6:10]) < 2012:
            valid = False

        if valid:
            self.__date_of_birthday = date_of_birthday
        else:
            raise ValueError("Incorrect input!")

    @property
    def total(self):
        return self.__total

    @total.setter
    def total(self, total: float):
        if total > 0:
            self.__total = total
        else:
            raise ValueError("Incorrect input!")

    @property
    def orders(self):
        return self.__orders

    @orders.setter
    def orders(self, orders: int):
        if orders > 0:
            self.__orders = orders
        else:
            raise ValueError("Incorrect input!")
