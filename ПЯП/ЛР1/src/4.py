def payout(amount):
    if amount < 8:
        return "Сумма должна быть больше 7 рублей."

    for five_ruble_bills in range(0, amount // 5 + 1):
        remaining_amount = amount - five_ruble_bills * 5
        if remaining_amount % 3 == 0:
            three_ruble_bills = remaining_amount // 3
            return f"Выплата: {three_ruble_bills} трехрублевых \
        и {five_ruble_bills} пятирублевых купюр."

    return "Невозможно выплатить данную сумму с использованием трех- \
        и пятирублевых купюр."


amount = int(input("Введите сумму для выплаты (более 7 рублей): "))
print(payout(amount))
10
