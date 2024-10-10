import tkinter as tk
from tkinter import messagebox
import numpy as np

default_X = X = {1, 2, 3, 4, 5, 6}


def relation_R(X):
    """Возвращает бинарное отношение R для множества X."""
    return {(m, n) for m in X for n in X if m % 3 == n % 3}


def relation_Q(X):
    """Возвращает бинарное отношение Q для множества X."""
    return {(m, n) for m in X for n in X if (m - n) >= 2}


def composition_R_Q(R, Q):
    """Возвращает композицию отношений R и Q."""
    return {(m, p) for m, n1 in R for n2, p in Q if n1 == n2}


def relation_matrix(X, relation):
    """Возвращает матрицу отношения для заданного множества X и отношения."""
    matrix = np.zeros((len(X), len(X)), dtype=int)
    elements = list(X)
    for m, n in relation:
        matrix[elements.index(m)][elements.index(n)] = 1
    return matrix


def domain_and_range(relation):
    """Возвращает область определения и область значений для отношения."""
    domain = {m for m, n in relation}
    range_ = {n for m, n in relation}
    return domain, range_


def is_reflexive(X, relation):
    """Проверяет, является ли отношение рефлексивным."""
    return all((x, x) in relation for x in X)


def is_symmetric(relation):
    """Проверяет, является ли отношение симметричным."""
    return all((n, m) in relation for m, n in relation)


def is_transitive(relation):
    """Проверяет, является ли отношение транзитивным."""
    return all(
        (m, p) in relation for m, n1 in relation for n2, p in relation if n1 == n2
    )


def reflexive_closure(X, relation):
    """Возвращает рефлексивное замыкание отношения."""
    return relation | {(x, x) for x in X}


def symmetric_closure(relation):
    """Возвращает симметричное замыкание отношения."""
    return relation | {(n, m) for m, n in relation}


def transitive_closure(X, relation):
    """Возвращает транзитивное замыкание отношения."""
    matrix = relation_matrix(X, relation)
    elements = list(X)
    n = len(X)

    for k in range(n):
        for i in range(n):
            for j in range(n):
                matrix[i][j] = matrix[i][j] or (matrix[i][k] and matrix[k][j])

    closure_relation = set()
    for i in range(n):
        for j in range(n):
            if matrix[i][j]:
                closure_relation.add((elements[i], elements[j]))
    return closure_relation


def show_results():
    """Отображает результаты отношений и их свойства."""
    global X
    if not X:
        messagebox.showerror(
            "Ошибка", "Пожалуйста, задайте множество X перед получением результатов."
        )
        return

    R = relation_R(X)
    Q = relation_Q(X)
    R_composed_Q = composition_R_Q(R, Q)

    results = f"Исходное бинарное отношение R:\n{R}\n"
    results += f"Исходное бинарное отношение Q:\n{Q}\n"
    results += f"Композиция R○Q:\n{R_composed_Q}\n\n"

    domain_R, range_R = domain_and_range(R)
    domain_Q, range_Q = domain_and_range(Q)

    results += f"Область определения R: {domain_R},\nОбласть значений R: {range_R}\n"
    results += f"Область определения Q: {domain_Q},\nОбласть значений Q: {range_Q}\n\n"

    results += f"Свойства отношения R:\n"
    results += f"Рефлексивность: {is_reflexive(X, R)}\n"
    results += f"Симметричность: {is_symmetric(R)}\n"
    results += f"Транзитивность: {is_transitive(R)}\n\n"

    results += f"Свойства отношения Q:\n"
    results += f"Рефлексивность: {is_reflexive(X, Q)}\n"
    results += f"Симметричность: {is_symmetric(Q)}\n"
    results += f"Транзитивность: {is_transitive(Q)}\n"

    messagebox.showinfo("Результаты", results)


def calculate_closure():
    """Расчитывает замыкание выбранного отношения."""
    closure_type = closure_var.get()
    relation_choice = relation_var.get()

    if not X:
        messagebox.showerror(
            "Ошибка", "Пожалуйста, задайте множество X перед расчетом замыкания."
        )
        return

    R = relation_R(X)
    Q = relation_Q(X)
    R_composed_Q = composition_R_Q(R, Q)

    if relation_choice == "R":
        selected_relation = R
    elif relation_choice == "Q":
        selected_relation = Q
    elif relation_choice == "R○Q":
        selected_relation = R_composed_Q
    else:
        messagebox.showerror("Ошибка", "Неверный выбор отношения!")
        return

    if closure_type == "рефлексивное":
        closure = reflexive_closure(X, selected_relation)
    elif closure_type == "симметричное":
        closure = symmetric_closure(selected_relation)
    elif closure_type == "транзитивное":
        closure = transitive_closure(X, selected_relation)
    else:
        messagebox.showerror("Ошибка", "Неверный выбор замыкания!")
        return

    result_message = f"Исходное бинарное отношение:\n{selected_relation}\n"
    result_message += f"Результат замыкания:\n{closure}"

    messagebox.showinfo("Замыкание", result_message)


def set_custom_set():
    """Устанавливает пользовательское множество X."""
    global X
    X = default_X
    input_value = entry_X.get()
    if input_value:
        try:
            X = set(map(int, input_value.split(",")))
        except ValueError:
            messagebox.showerror(
                "Ошибка", "Введите корректные числа, разделенные запятыми."
            )
            return


root = tk.Tk()
root.title("Отношения и замыкания")
root.geometry("400x400")

label_X = tk.Label(
    root, text="Введите множество X\n(через запятую, по умолчанию 1,2,3,4,5,6):"
)
label_X.pack(pady=10)

entry_X = tk.Entry(root)
entry_X.pack(pady=10)

set_button = tk.Button(root, text="Установить множество X", command=set_custom_set)
set_button.pack(pady=10)

results_button = tk.Button(root, text="Показать результаты", command=show_results)
results_button.pack(pady=10)

relation_var = tk.StringVar(value="R")
relation_label = tk.Label(root, text="Выберите отношение:")
relation_label.pack()
relation_options = ["R", "Q", "R○Q"]
relation_menu = tk.OptionMenu(root, relation_var, *relation_options)
relation_menu.pack()

closure_var = tk.StringVar(value="рефлексивное")
closure_label = tk.Label(root, text="Выберите замыкание:")
closure_label.pack()
closure_options = ["рефлексивное", "симметричное", "транзитивное"]
closure_menu = tk.OptionMenu(root, closure_var, *closure_options)
closure_menu.pack()

closure_button = tk.Button(root, text="Рассчитать замыкание", command=calculate_closure)
closure_button.pack(pady=10)

root.mainloop()
