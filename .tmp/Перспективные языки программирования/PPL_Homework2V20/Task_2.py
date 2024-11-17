import os
import csv
from enum import Enum
from shoppers import Shopper


class Commands(Enum):
    DELETE_SHOPPER = 1
    ADD_SHOPPER = 2
    CHANGE_SHOPPER = 3
    GET_SHOPPER_INFO = 4
    SORT_SHOPPERS_NAME = 5
    SORT_SHOPPERS_DATE_OF_BIRTHDAY = 6
    SORT_SHOPPERS_TOTAL = 7
    SORT_SHOPPERS_ORDERS = 8
    SAVE_IN_CSV_FILE = 9
    LOAD_FROM_CSV_FILE = 10
    PRINT_SHOPPERS = 11
    INDIVIDUAL_TASK = 12
    EXIT = 0


def input_int(message: str, start: int, end: int) -> int:
    valid = False
    n = 0
    while not valid:
        try:
            n = int(input(message))
        except ValueError:
            print('Вы ввели не число. Попробуйте снова.')
        else:
            if start <= n <= end:
                valid = True
            else:
                print('Введённое число вне диапазона!')
    return n


def input_shopper(data: list[Shopper]) -> Shopper:
    """Добавление записи о покупателе"""
    new_shopper = Shopper()
    new_id, valid_id = -1, False
    while not valid_id:
        new_id = int(input("Введите ID покупателя: "))
        valid_id = new_id not in list(i.shopper_id for i in data)
        if not valid_id:
            print("ID должен быть уникальным!")
    valid = False
    while not valid:
        try:
            new_shopper.shopper_id = new_id
            new_shopper.name = input("Введите ФИО: ")
            new_shopper.date_of_birthday = input("Введите дату рождения: ")
            new_shopper.total = int(input("Введите общую сумму покупок: "))
            new_shopper.orders = int(input("Введите количество заказов: "))
        except ValueError:
            print("Неккоректный ввод! Попробуйте снова.")
        except IndexError:
            print("Неккоректный ввод! Попробуйте снова.")
        else:
            valid = True
    return new_shopper


def m_print_shoppers(data: list[Shopper]):
    """Вывод списка покупателей"""
    if not data:
        print("Список пустой!")
    else:
        print("Покупатели:")
        for i in data:
            print(i)
            print()


def m_add_shopper(data: list[Shopper]):
    """Добавление покупателя"""
    data.append(input_shopper(data))


def m_delete_shopper(data: list[Shopper]):
    """Удаление покупателя"""
    if not data:
        print("Список пустой!")
    else:
        shopper_id = int(input("Введите ID удаляемого покупателя: "))
        index = -1
        for i in range(len(data)):
            if data[i].shopper_id == shopper_id:
                index = i
                break
        if index != -1:
            data.pop(index)
            print(f"Покупатель с ID {shopper_id} удалён")
        else:
            print("Покупателя с таким ID не существует!")


def m_change_shopper(data: list[Shopper]):
    """Изменение информации о покупателе"""
    if not data:
        print("Список пустой!")
    else:
        shopper_id = int(input("Введите ID изменяемого покупателя "))
        index = -1
        for i in range(len(data)):
            if data[i].shopper_id == shopper_id:
                index = i
                break
        if index != -1:
            data[index] = input_shopper(data)
        else:
            print("Покупателя с таким ID не существует!")


def m_get_shopper_info(data: list[Shopper]):
    """Получить информацию о покупателе"""
    if not data:
        print("Список пустой!")
    else:
        shopper_id = int(input("Введите ID просматриваемого покупателя: "))
        find_shopper = False
        for i in data:
            if i.shopper_id == shopper_id:
                find_shopper = True
                print(i)
        if not find_shopper:
            print("Покупателя с таким ID не существует!")


def m_sort_shoppers_name(data: list[Shopper]):
    """Сортировка по имени"""
    data.sort(key=lambda x: x.name)
    print("Покупатели отсортированы по ФИО")


def m_sort_shoppers_date_of_birthday(data: list[Shopper]):
    """Сортировка по дате рождения"""
    data.sort(key=lambda x: x.date_of_birthday)
    print("Покупатели отсортированы по дате рождения")


def m_sort_shoppers_total(data: list[Shopper]):
    """Сортировка по общей сумме покупок"""
    data.sort(key=lambda x: x.total)
    print("Покупатели отсортированы по общей сумме покупок")


def m_sort_shoppers_orders(data: list[Shopper]):
    """Сортировка по количеству заказов"""
    data.sort(key=lambda x: x.orders)
    print("Покупатели отсортированы по количеству заказов")


def m_save_in_csv_file(data: list[Shopper], data_file: str):
    """Сохранение данных в csv-файл"""
    with open(data_file, 'w', encoding='utf8', newline='') as file:
        writer = csv.writer(file)
        for i in data:
            if i:
                writer.writerow([i.shopper_id, i.name, i.date_of_birthday, i.total, i.orders])
    print("Данные успешно сохранены в файл")


def m_load_from_csv_file(data: list[Shopper], data_file: str):
    """Загрузка данных из csv-файла"""
    with open(data_file, 'r', encoding='utf8') as file:
        reader = csv.reader(file)
        for curr_shopper in reader:
            if curr_shopper:
                shopper = Shopper()
                print(curr_shopper)
                shopper.shopper_id = int(curr_shopper[0])
                shopper.name = curr_shopper[1]
                shopper.date_of_birthday = curr_shopper[2]

                shopper.total = int(curr_shopper[3])
                shopper.orders = int(curr_shopper[4])
                data.append(shopper)
    print("Данные успешно загружены из файла")


def m_individual_task(data: list[Shopper], data_file: str):
    """Индивидуальное задание"""
    m_sort_shoppers_total(data)
    min_total = data[0]
    m_sort_shoppers_orders(data)
    min_orders = data[0]

    with open(data_file, 'w', encoding='utf8', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([min_total.shopper_id, min_total.name, min_total.date_of_birthday,
                         min_total.total, min_total.orders])
        writer.writerow([min_orders.shopper_id, min_orders.name, min_orders.date_of_birthday,
                         min_orders.total, min_orders.orders])
    print("Информация о покупателе с минимальной общей суммой заказа загружена в файл")
    print("Информация о покупателе с минимальным количеством заказов загружена в файл")


def print_menu():
    """Меню"""
    print(f" 1. Удалить запись по id\n"
          f" 2. Добавить новую запись\n"
          f" 3. Изменить запись по id\n"
          f" 4. Получить информацию по id\n"
          f" 5. Сортировка по ФИО\n"
          f" 6. Сортировка по дате рождения\n"
          f" 7. Сортировка по общей сумме покупок\n"
          f" 8. Сортировка по количеству заказов\n"
          f" 9. Сохранить данные в файл\n"
          f"10. Загрузить данные из файла\n"
          f"11. Вывести данные\n"
          f"12. Индивидуальное задание\n"
          f" 0. Выход")


def main():
    """Основная логика программы"""
    _exit = False
    data_file = 'data.csv'
    individual_task_file = 'task.csv'
    data = []
    while not _exit:
        os.system('cls')
        print_menu()
        command = input_int("Введите команду: ", 0, 12)
        if command == Commands.DELETE_SHOPPER.value:
            m_delete_shopper(data)
        elif command == Commands.ADD_SHOPPER.value:
            m_add_shopper(data)
        elif command == Commands.CHANGE_SHOPPER.value:
            m_change_shopper(data)
        elif command == Commands.GET_SHOPPER_INFO.value:
            m_get_shopper_info(data)
        elif command == Commands.SORT_SHOPPERS_NAME.value:
            m_sort_shoppers_name(data)
        elif command == Commands.SORT_SHOPPERS_DATE_OF_BIRTHDAY.value:
            m_sort_shoppers_date_of_birthday(data)
        elif command == Commands.SORT_SHOPPERS_TOTAL.value:
            m_sort_shoppers_total(data)
        elif command == Commands.SORT_SHOPPERS_ORDERS.value:
            m_sort_shoppers_orders(data)
        elif command == Commands.SAVE_IN_CSV_FILE.value:
            m_save_in_csv_file(data, data_file)
        elif command == Commands.LOAD_FROM_CSV_FILE.value:
            m_load_from_csv_file(data, data_file)
        elif command == Commands.PRINT_SHOPPERS.value:
            m_print_shoppers(data)
        elif command == Commands.INDIVIDUAL_TASK.value:
            m_individual_task(data, individual_task_file)
        elif command == Commands.EXIT.value:
            _exit = True
        if not _exit:
            os.system('pause')


if __name__ == '__main__':
    main()
