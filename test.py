def v():
    mas = [1, 3, 5, 6]
    a = "stfrsgg"
    f = 1324
    ma = [1, 2, 3]
    for i in mas:
        yield i


print(v().__sizeof__())
print(v().__next__())
print(v().__sizeof__())
