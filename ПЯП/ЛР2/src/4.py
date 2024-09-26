necessary_items = set(
    input("Введите необходимые для учёбы вещи через запятую: ").split(", ")
)

mari_bag_items = set(
    input("Введите вещи, находящиеся в сумке у Мари через запятую: ").split(", ")
)

missing_items = necessary_items - mari_bag_items  # Вещи, которых не хватает
unnecessary_items = mari_bag_items - necessary_items  # Ненужные вещи

print("Вещи, которых Мари не хватает:", missing_items)
print("Ненужные вещи в сумке Мари:", unnecessary_items)
