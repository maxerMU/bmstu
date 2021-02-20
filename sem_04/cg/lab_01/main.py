import sys
from PyQt5 import QtWidgets, QtCore
from PyQt5.QtWidgets import QTableWidgetItem

import design
from canvas import Canvas
from points import Points, Point, NoTriangleException

class App(QtWidgets.QMainWindow, design.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.points_table.setHorizontalHeaderLabels(("x", "y"))

        self.canvas = Canvas(self.centralwidget)
        self.canvas.setGeometry(QtCore.QRect(470, 170, 731, 761))
        self.canvas.setObjectName("canvas")

        self.add_point_btn.clicked.connect(self.add_point)
        self.back_button.clicked.connect(self.back)
        self.del_btn.clicked.connect(self.del_point)
        self.task_btn.clicked.connect(self.task)
        self.run_btn.clicked.connect(self.find)
    
    def add_point(self):
        try:
            x = float(self.x_val_input.text())
            y = float(self.y_val_input.text())

            self.points_table.setRowCount(self.points_table.rowCount() + 1)

            self.points_table.setItem(self.points_table.rowCount() - 1, 0, QTableWidgetItem(str(x)))
            self.points_table.setItem(self.points_table.rowCount() - 1, 1, QTableWidgetItem(str(y)))
        except Exception:
            msgbox = QtWidgets.QMessageBox()

            msgbox.setText("Координаты должны быть действительными числами. " +
                           "Целая и дробная части разделяются точкой")

            msgbox.exec_()
    
    def back(self):
        self.points_table.removeRow(self.points_table.rowCount() - 1)

    def del_point(self):
        try:
            num = int(self.del_num_input.text())

            self.points_table.removeRow(num - 1)
        except Exception:
            msgbox = QtWidgets.QMessageBox()
            msgbox.setText("Номер точки должен быть целым положительным числом, " +
                           "соответствующем номеру в таблице.")
            msgbox.exec_()

    def task(self):
        msgbox = QtWidgets.QMessageBox()
        msgbox.setWindowTitle("Условие")
        msgbox.setText("На плоскости дано множество точек. Найти такой треугольник с вершинами " +
                       "в этих точках, для которого разность количеств точек попавших внутрь треугольника "
                       "и за его пределы, но внутри описанной окружности, минимальна")
        msgbox.exec_()

    def find(self):
        self.canvas.shapes = []
        points = []
        for num in range(1, self.points_table.rowCount() + 1):
            x = float(self.points_table.item(num - 1, 0).text())
            y = float(self.points_table.item(num - 1, 1).text())
            p = Point(x, y, num)
            if not (p in points):
                points.append(p)

        if len(points) < 3:
            self.not_enough_points()

            return None

        field = Points(points, self.canvas, 0.05)

        try:
            field.draw_res()
        except NoTriangleException:
            self.no_triangle()

    def not_enough_points(self):
        msgbox = QtWidgets.QMessageBox()
        msgbox.setText("Минимальное число разных точек - 3")
        msgbox.exec_()

    def no_triangle(self):
        msgbox = QtWidgets.QMessageBox()
        msgbox.setText("Все треугольники вырожденные")
        msgbox.exec_()


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = App()
    window.show()
    app.exec_()

if __name__ == "__main__":
    main()
