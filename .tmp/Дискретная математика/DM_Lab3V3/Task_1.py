from math import factorial


print("Определение перестановки по её номеру")
n = int(input("Введите количество первых натуральных чисел n: "))
num = int(input("Введите номер перестановки num: "))

if 0 < num - 1 < factorial(n):
    print(f"Перестановка под номером {num}:", end=' ')
    num -= 1
    val = [i for i in range(n + 1)]
    res = 0                                             # Результат
    for i in range(1, n):
        group = factorial(n - i)                        # Номер группы для i-той цифры
        res += val[num // group + 1] * 10 ** (n - i)    # Запись цифры в результат
        val.pop(num // group + 1)                       # Удаление использованной цифры
        num %= group                                    # Номер следующей группы
    res += val[1]                                       # Дозапись неиспользованной цифры
    print(res)
else:
    print("Введён неверный номер перестановки!")
