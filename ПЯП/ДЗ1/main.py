import sys
from PyQt6.QtWidgets import (
    QApplication,
    QMainWindow,
    QMessageBox,
    QCheckBox,
    QLabel,
    QPushButton,
    QGraphicsScene,
    QGraphicsView,
)
from PyQt6 import uic
from PyQt6.QtGui import QPen, QColor
import numpy as np


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        uic.loadUi("main.ui", self)

        self.plot_button = self.findChild(QPushButton, "plotButton")
        self.calculate_button = self.findChild(QPushButton, "calculateButton")
        self.about_button = self.findChild(QPushButton, "about")
        self.product1 = self.findChild(QCheckBox, "product1")
        self.product2 = self.findChild(QCheckBox, "product2")
        self.product3 = self.findChild(QCheckBox, "product3")
        self.label = self.findChild(QLabel, "label")

        self.plot_button.clicked.connect(self.plot_graph)
        self.calculate_button.clicked.connect(self.calculate_total)
        self.about_button.clicked.connect(self.show_info)

        self.scene = QGraphicsScene(self)
        self.graphics_view = self.findChild(QGraphicsView, "graphicsView")
        self.graphics_view.setScene(self.scene)

    def plot_graph(self):
        self.scene.clear()

        x = np.linspace(-4, 4, 200)
        y = np.abs(np.sin(5 * x)) / np.sin(x - 1)

        pen = QPen(QColor(0, 0, 255))
        for i in range(len(x) - 1):
            x1 = x[i] * 50
            y1 = -y[i] * 50
            x2 = x[i + 1] * 50
            y2 = -y[i + 1] * 50

            self.scene.addLine(x1, y1, x2, y2, pen)

        self.scene.addLine(-200, 0, 200, 0, QPen(QColor(0, 0, 0), 1))  # Ось X
        self.scene.addLine(0, -200, 0, 200, QPen(QColor(0, 0, 0), 1))  # Ось Y

        self.scene.setSceneRect(-200, -200, 400, 400)  # Установка границ сцены

    def calculate_total(self):
        total_price = 0
        if self.product1.isChecked():
            total_price += 100
        if self.product2.isChecked():
            total_price += 200
        if self.product3.isChecked():
            total_price += 300

        self.label.setText(f"Итоговая цена: {total_price} руб.")

    def show_info(self):
        info = """
        ФИО: Суриков Никита Сергеевич
        Специальность: Программная инженерия
        Группа: ИУК4-31Б
        """
        QMessageBox.information(self, "Информация", info)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
