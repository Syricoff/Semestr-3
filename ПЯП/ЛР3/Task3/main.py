from holiday import Holiday

holiday_name = input("Введите название праздника: ")
invited_name = input("Введите имя приглашенного: ")
invited_count = int(input("Введите количество персон в приглашении: "))

holiday = Holiday(holiday_name, invited_name, invited_count)

result = holiday.family()
print(result)
