from matplotlib import pyplot as plt
from matplotlib_venn import venn3, venn3_circles
from itertools import product


def get_logical_formula():
    """
    Запрашивает у пользователя ввод логической формулы.

    :return: Логическая формула в виде строки.
    """
    formula = input("Введите логическую формулу (используйте A, B, C): ")
    return formula


def list_regions(logical_formula):
    """
    Генерирует все регионы, удовлетворяющие заданной логической формуле.

    :param logical_formula:
    Логическая формула в виде строки, использующая переменные A, B, C.
    :yield: Регион в виде строки (например, "010").
    """
    for values in product([False, True], repeat=3):
        try:
            if eval(logical_formula, {}, dict(zip("ABC", values))):
                yield "".join(map(str, map(int, values)))
        except Exception as e:
            print(f"Ошибка при оценке формулы: {e}")


def plot_diagram(logical_formula):
    """
    Создает диаграмму Венна по заданной логической формуле.

    :param logical_formula:
    Логическая формула в виде строки, использующая переменные A, B, C.
    """
    figure, ax = plt.subplots(figsize=(7, 7))

    venn_diagram = venn3(
        alpha=1.0,
        subsets=(1,) * 7,
        set_colors=("white",) * 3,
        subset_label_formatter=lambda x: "",
    )

    venn3_circles(subsets=[1] * 7, linestyle="solid")

    regions_to_color = list(list_regions(logical_formula))

    for region in regions_to_color:
        if region == "000":
            ax.set_facecolor("lightgrey")
        else:
            patch = venn_diagram.get_patch_by_id(region)
            if patch:
                patch.set_color("lightgrey")
            else:
                print(f"Регион {region} не найден")

    plt.annotate("U", (-0.660, -0.675))
    plt.axis("on")
    plt.show()


if __name__ == "__main__":
    logical_formula = get_logical_formula()
    plot_diagram(logical_formula)
