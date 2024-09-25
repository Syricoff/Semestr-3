def is_reverse_alphabetical(s):
    filtered_str = "".join(filter(str.isalpha, s.lower()))

    return filtered_str == "".join(sorted(filtered_str, reverse=True))


input_string = input("Введите строку: ")
if is_reverse_alphabetical(input_string):
    print("Буквы располагаются в порядке, обратном алфавитному.")
else:
    print("Буквы не располагаются в порядке, обратном алфавитному.")
