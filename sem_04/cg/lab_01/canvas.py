from  math import sin, cos, radians
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QPainter, QBrush, QColor, QPen

class Figure():
    def __init__(self, color, width):
        self.color = color
        self.width = width
    
    def paint(self, painter):
        pass

class Point(Figure):
    def __init__(self, x, y, x_draw, y_draw, num, color, width):
        super().__init__(color, width)
        self.x = x
        self.y = y
        self.x_draw = x_draw
        self.y_draw = y_draw
        self.num = num
    
    def paint(self, painter):
        pen = QPen(QColor(*self.color))
        brush = QBrush(QColor(*self.color))

        painter.setPen(pen)
        painter.setBrush(brush)

        painter.drawEllipse(self.x - self.width / 2, self.y - self.width / 2, self.width, self.width)
        painter.drawText(self.x - self.width, self.y - self.width, str(f"{self.num} ({self.x_draw}; {self.y_draw})"))
        #painter.drawText(self.x - self.width, self.y - self.width, str(f"{self.num}"))

class Line(Figure):
    def __init__(self, x1, y1, x2, y2, color, width):
        super().__init__(color, width)
        self.x1, self.y1, self.x2, self.y2 = x1, y1, x2, y2

    def paint(self, painter):
        pen = QPen(QColor(*self.color))
        painter.setPen(pen)

        painter.drawLine(self.x1, self.y1, self.x2, self.y2)

        painter.setPen(pen)

class Circle(Figure):
    def __init__(self, x, y, r, color, width):
        super().__init__(color, width)
        self.x = x
        self.y = y
        self.r = r
    
    def paint(self, painter):
        pen = QPen(QColor(*self.color))
        pen.setWidth(self.width)

        painter.setPen(pen)

        painter.drawEllipse(self.x - self.r, self.y - self.r, self.r * 2, self.r * 2)

class Triangle(Figure):
    def __init__(self, x1, y1, x2, y2, x3, y3, color, width):
        super().__init__(color, width)

        self.x1, self.x2, self.x3 = x1, x2, x3
        self.y1, self.y2, self.y3 = y1, y2, y3

    def paint(self, painter):
        pen = QPen(QColor(*self.color))
        pen.setWidth(self.width)

        painter.setPen(pen)
        painter.drawLine(self.x1, self.y1, self.x2, self.y2)
        painter.drawLine(self.x3, self.y3, self.x2, self.y2)
        painter.drawLine(self.x1, self.y1, self.x3, self.y3)

class Arrow(Figure):
    def __init__(self, x1, y1, x2, y2, dx1, dy1, dx2, dy2, color, width):
        super().__init__(color, width)

        self.x1, self.x2 = x1, x2
        self.y1, self.y2 = y1, y2
        self.dx1, self.dy1 = dx1, dy1
        self.dx2, self.dy2 = dx2, dy2

    def paint(self, painter):
        pen = QPen(QColor(*self.color))
        pen.setWidth(self.width)

        painter.setPen(pen)
        painter.drawLine(self.x1, self.y1, self.x2, self.y2)
        painter.drawLine(self.x2, self.y2, self.x2 + self.dx1, self.y2 + self.dy1)
        painter.drawLine(self.x2, self.y2, self.x2 + self.dx2, self.y2 + self.dy2)

class Canvas(QWidget):
    def __init__(self, root):
        super().__init__(root)

        self.shapes = []

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)

        for shape in self.shapes:
            shape.paint(painter)

        painter.end()

    def draw_point(self, x, y, x_draw, y_draw, num, color, width):
        p = Point(x, y, x_draw, y_draw, num, color, width)
        self.shapes.append(p)

        self.update()

    def draw_circle(self, x, y, r, color, width):
        c = Circle(x, y, r, color, width)
        self.shapes.append(c)

        self.update()

    def draw_triangle(self, x1, y1, x2, y2, x3, y3, color, width):
        t = Triangle(x1, y1, x2, y2, x3, y3, color, width)
        self.shapes.append(t)

        self.update()

    def draw_line(self, x1, y1, x2, y2, color, width):
        l = Line(x1, y1, x2, y2, color, width)
        self.shapes.append(l)

        self.update()

    def draw_arrow(self, x1, y1, x2, y2, dx1, dy1, dx2, dy2, color, width):
        a = Arrow(x1, y1, x2, y2, dx1, dy1, dx2, dy2, color, width)
        self.shapes.append(a)

        self.update()
