def cube_root(x):
    y = x

    while True:
        y_next = (1 / 3) * (2 * y + x / (y**2))
        if abs(y_next - y) < 1e-5:
            break
        y = y_next
    return y


x = float(input("Введите вещественное число x: "))
result = cube_root(x)
print(f"Приближенное значение кубического корня из {x} равно {result:.6f}")
