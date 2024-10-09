import matplotlib.pyplot as plt

universities_data = {
    "Москва": 20,
    "Санкт-Петербург": 15,
    "Новосибирск": 10,
    "Екатеринбург": 8,
    "Казань": 7,
    "Нижний Новгород": 7,
    "Челябинск": 5,
    "Самара": 5,
    "Уфа": 4,
    "Ростов-на-Дону": 4,
    "Волгоград": 3,
    "Тюмень": 3,
    "Красноярск": 3,
    "Пермь": 2,
    "Ижевск": 2,
    "Калуга": 1,
}

cities = list(universities_data.keys())
universities_count = list(universities_data.values())

plt.figure(figsize=(8, 8))
plt.pie(universities_count, labels=cities, autopct="%1.1f%%", startangle=0)
plt.title("Распределение технических университетов по городам России")
plt.axis("equal")
plt.show()
