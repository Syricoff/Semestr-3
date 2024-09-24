import sys
from PyQt5 import QtWidgets
from ui import Ui_MainWindow

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from matplotlib.figure import Figure
import numpy as np


class Homework(QtWidgets.QMainWindow):
    """Основной класс для логики"""
    quantity = 0

    def __init__(self):
        """Инициализация наследуемого класса"""
        super(Homework, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.init_UI()

    def init_UI(self):
        """Основная логика программы"""
        self.ui.btn1.clicked.connect(self.task_1)
        self.ui.btn2.clicked.connect(self.task_2)
        self.ui.btn3.clicked.connect(lambda: print("Обращение за справкой"))
        self.ui.btn4.clicked.connect(self.fill)
        self.ui.btn5.clicked.connect(self.buy)
        self.ui.btnexit1.clicked.connect(sys.exit)
        self.ui.btnexit2.clicked.connect(lambda: self.ui.MainMenu.setCurrentIndex(0))
        self.ui.btnexit3.clicked.connect(lambda: self.ui.MainMenu.setCurrentIndex(0))

    def task_1(self):
        """Первое задание"""
        self.ui.MainMenu.setCurrentIndex(1)
        fig = Figure(figsize=(5, 5))
        can = FigureCanvasQTAgg(fig)
        layout = QtWidgets.QVBoxLayout(self.ui.widget)
        layout.addWidget(can)
        ax = can.figure.add_subplot(111)
        ax.cla()

        x = np.arange(-10, 10, 0.1)
        y = np.cos(x) * np.cos(x) * np.cos(x) * np.sin(x)
        for i in range(0, len(y)):
            y[i] = y[i] - (5 * x[i]) / (np.sin(2 * x[i]) * np.cos(x[i]))

        ax.plot(x, y)
        ax.grid(True)
        can.figure.tight_layout()
        can.draw()

    def task_2(self):
        """Второе задание"""
        self.ui.MainMenu.setCurrentIndex(2)
        self.ui.lab4.setHidden(True)

    def fill(self):
        """Пополнение склада"""
        self.ui.lab2.clear()
        fill_up = self.ui.le1.text()
        self.ui.le1.clear()
        self.quantity += int(fill_up)
        self.ui.lab2.setText(str(self.quantity))
        self.ui.lab4.setText("Пополнение выполнено успешно!")
        self.ui.lab4.setHidden(False)

    def buy(self):
        """Покупка"""
        self.ui.lab2.clear()
        fill_down = self.ui.le2.text()
        if self.quantity < int(fill_down):
            self.ui.lab4.setText("Недостаточно товара на складе!")
        else:
            self.quantity -= int(fill_down)
            self.ui.lab4.setText("Покупка выполнена успешно!")
        self.ui.le2.clear()
        self.ui.lab2.setText(str(self.quantity))
        self.ui.lab4.setHidden(False)


app = QtWidgets.QApplication([])
application = Homework()
application.show()

sys.exit(app.exec())
