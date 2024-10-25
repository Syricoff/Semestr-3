import xml.etree.ElementTree as ET
import os


class CarManager:
    def __init__(self, xml_file):
        self.xml_file = xml_file
        self.create_xml_file()

    def create_xml_file(self):
        """Создает XML-файл, если он не существует."""
        if not os.path.exists(self.xml_file):
            root = ET.Element("cars")
            self.add_test_data(root)
            tree = ET.ElementTree(root)
            tree.write(self.xml_file)

    def add_test_data(self, root):
        """Добавляет тестовые данные о автомобилях."""
        test_cars = [
            {"license_plate": "A123BC", "brand": "Toyota", "color": "Red", "owner": "Ivanov Ivan"},
            {"license_plate": "B456CD", "brand": "BMW", "color": "Black", "owner": "Petrov Petr"},
            {"license_plate": "C789EF", "brand": "Audi", "color": "Blue", "owner": "Sidorov Sidor"},
        ]

        for car in test_cars:
            car_element = ET.Element("car")
            ET.SubElement(car_element, "license_plate").text = car["license_plate"]
            ET.SubElement(car_element, "brand").text = car["brand"]
            ET.SubElement(car_element, "color").text = car["color"]
            ET.SubElement(car_element, "owner").text = car["owner"]
            root.append(car_element)

    def add_car(self, license_plate, brand, color, owner):
        """Добавляет новую запись о автомобиле."""
        tree = ET.parse(self.xml_file)
        root = tree.getroot()

        car = ET.Element("car")
        ET.SubElement(car, "license_plate").text = license_plate
        ET.SubElement(car, "brand").text = brand
        ET.SubElement(car, "color").text = color
        ET.SubElement(car, "owner").text = owner

        root.append(car)
        tree.write(self.xml_file)

    def remove_car(self, license_plate):
        """Удаляет запись о автомобиле по гос. номеру."""
        tree = ET.parse(self.xml_file)
        root = tree.getroot()

        for car in root.findall("car"):
            if car.find("license_plate").text == license_plate:
                root.remove(car)
                break

        tree.write(self.xml_file)

    def update_car(self, license_plate, brand=None, color=None, owner=None):
        """Изменяет запись о автомобиле по гос. номеру."""
        tree = ET.parse(self.xml_file)
        root = tree.getroot()

        for car in root.findall("car"):
            if car.find("license_plate").text == license_plate:
                if brand:
                    car.find("brand").text = brand
                if color:
                    car.find("color").text = color
                if owner:
                    car.find("owner").text = owner
                break

        tree.write(self.xml_file)

    def get_car_info(self, license_plate):
        """Получает информацию о автомобиле по гос. номеру."""
        tree = ET.parse(self.xml_file)
        root = tree.getroot()

        for car in root.findall("car"):
            if car.find("license_plate").text == license_plate:
                return {
                    "license_plate": car.find("license_plate").text,
                    "brand": car.find("brand").text,
                    "color": car.find("color").text,
                    "owner": car.find("owner").text,
                }
        return None

    def sort_cars(self, by):
        """Сортирует автомобили по указанному критерию."""
        tree = ET.parse(self.xml_file)
        root = tree.getroot()
        cars = [car for car in root.findall("car")]

        if by == "brand":
            cars.sort(key=lambda x: x.find("brand").text)
        elif by == "color":
            cars.sort(key=lambda x: x.find("color").text)
        elif by == "owner":
            cars.sort(key=lambda x: x.find("owner").text)

        return cars

    def get_cars_by_owner(self, owner):
        """Получает все автомобили, принадлежащие заданному владельцу."""
        tree = ET.parse(self.xml_file)
        root = tree.getroot()

        owner_cars = []
        for car in root.findall("car"):
            if car.find("owner").text == owner:
                owner_cars.append(
                    {
                        "license_plate": car.find("license_plate").text,
                        "brand": car.find("brand").text,
                        "color": car.find("color").text,
                        "owner": car.find("owner").text,
                    }
                )

        return owner_cars

    def display_all_cars(self):
        """Выводит информацию о всех автомобилях."""
        tree = ET.parse(self.xml_file)
        root = tree.getroot()

        for car in root.findall("car"):
            print(
                f"{car.find('license_plate').text}, {car.find('brand').text}, "
                f"{car.find('color').text}, {car.find('owner').text}"
            )


class MenuItem:
    def __init__(self, title, action):
        self.title = title
        self.action = action


class Menu:
    def __init__(self):
        self.items = []

    def add_item(self, title, action):
        self.items.append(MenuItem(title, action))

    def display(self):
        print("\nМеню:")
        for index, item in enumerate(self.items):
            print(f"{index + 1}. {item.title}")
        print("0. Выход")

    def execute(self, choice):
        if 0 < choice <= len(self.items):
            self.items[choice - 1].action()
        elif choice == 0:
            print("Выход из программы.")
            return True
        else:
            print("Неверный выбор, попробуйте снова.")
        return False


def main():
    car_manager = CarManager("cars.xml") 
    menu = Menu()

    # Добавляем пункты меню
    menu.add_item("Добавить новую запись", lambda: add_new_car(car_manager))
    menu.add_item("Удалить запись", lambda: remove_car(car_manager))
    menu.add_item("Изменить запись", lambda: update_car(car_manager))
    menu.add_item("Получить информацию о автомобиле", lambda: get_car_info(car_manager))
    menu.add_item("Отсортировать автомобили", lambda: sort_cars(car_manager))
    menu.add_item(
        "Получить автомобили по владельцу", lambda: get_cars_by_owner(car_manager)
    )
    menu.add_item("Вывести все автомобили", lambda: car_manager.display_all_cars())

    while True:
        menu.display()
        choice = int(input("Выберите действие: "))
        if menu.execute(choice):
            break


def add_new_car(car_manager):
    license_plate = input("Введите гос. номер: ")
    brand = input("Введите марку: ")
    color = input("Введите цвет: ")
    owner = input("Введите ФИО владельца: ")
    car_manager.add_car(license_plate, brand, color, owner)
    print("Запись добавлена.")


def remove_car(car_manager):
    license_plate = input("Введите гос. номер для удаления: ")
    car_manager.remove_car(license_plate)
    print("Запись удалена.")


def update_car(car_manager):
    license_plate = input("Введите гос. номер для изменения: ")
    brand = input("Введите новую марку (или оставьте пустым для пропуска): ")
    color = input("Введите новый цвет (или оставьте пустым для пропуска): ")
    owner = input("Введите новое ФИО владельца (или оставьте пустым для пропуска): ")
    car_manager.update_car(
        license_plate,
        brand if brand else None,
        color if color else None,
        owner if owner else None,
    )
    print("Запись изменена.")


def get_car_info(car_manager):
    license_plate = input("Введите гос. номер: ")
    car_info = car_manager.get_car_info(license_plate)
    if car_info:
        print(car_info)
    else:
        print("Автомобиль не найден.")


def sort_cars(car_manager):
    sort_by = input("Сортировать по (brand/color/owner): ")
    sorted_cars = car_manager.sort_cars(sort_by)
    for car in sorted_cars:
        print(
            f"{car.find('license_plate').text}, {car.find('brand').text}, "
            f"{car.find('color').text}, {car.find('owner').text}"
        )


def get_cars_by_owner(car_manager):
    owner = input("Введите ФИО владельца: ")
    owner_cars = car_manager.get_cars_by_owner(owner)
    if owner_cars:
        for car in owner_cars:
            print(car)
    else:
        print("Автомобили не найдены.")


if __name__ == "__main__":
    main()
