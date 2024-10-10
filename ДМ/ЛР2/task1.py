import tkinter as tk
from tkinter import messagebox


def decart(s1, s2):
    """Возвращает декартово произведение двух множеств."""
    return set((a, b) for a in s1 for b in s2)


def calculate_results():
    """Выполняет расчеты и отображает результаты."""
    try:
        # Получаем значения из полей ввода
        n1_values = entry_n1.get()
        n2_values = entry_n2.get()

        # Преобразуем строки в множества
        N1 = set(map(int, n1_values.split(",")))
        N2 = set(map(int, n2_values.split(",")))

        N1_x_N2 = decart(N1, N2)
        N2_x_N1 = decart(N2, N1)

        inter = N1_x_N2 & N2_x_N1
        union = N1_x_N2 | N2_x_N1

        N1_inter_N2 = N1 & N2
        inter_dec = decart(N1_inter_N2, N1_inter_N2)

        N1_union_N2 = N1 | N2
        union_dec = decart(N1_union_N2, N1_union_N2)

        results = (
            f"1. (N1 x N2) ∩ (N2 x N1): {inter}\n"
            f"2. (N1 x N2) ∪ (N2 x N1): {union}\n"
            f"3. (N1 ∩ N2) x (N1 ∩ N2): {inter_dec}\n"
            f"4. (N1 ∪ N2) x (N1 ∪ N2): {union_dec}"
        )

        messagebox.showinfo("Результаты", results)

    except ValueError:
        messagebox.showerror(
            "Ошибка", "Введите корректные числа, разделенные запятыми."
        )


root = tk.Tk()
root.title("Множества и операции")
root.geometry("400x300")

label_n1 = tk.Label(root, text="Введите множество N1 (через запятую):")
label_n1.pack(pady=5)

entry_n1 = tk.Entry(root)
entry_n1.pack(pady=5)

label_n2 = tk.Label(root, text="Введите множество N2 (через запятую):")
label_n2.pack(pady=5)

entry_n2 = tk.Entry(root)
entry_n2.pack(pady=5)

calculate_button = tk.Button(root, text="Рассчитать", command=calculate_results)
calculate_button.pack(pady=20)

root.mainloop()
