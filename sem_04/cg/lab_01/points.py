from math import fabs, sqrt

class NoTriangleException(Exception):
    pass

class Point():
    def __init__(self, x, y, num=-1):
        self.x = x
        self.y = y
        self.x_draw = x
        self.y_draw = y
        self.num = num

    def __eq__(self, other):
        eps = 1e-6
        return fabs(self.x - other.x) < eps and fabs(self.y - other.y) < eps

    def convert_to_draw(self, xc, yc, k):
        self.x = xc + self.x * k
        self.y = yc - self.y * k


class Triangle():
    def __init__(self, p1, p2, p3):
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3

    def is_correct(self):
        eps = 1e-6

        a = sqrt((self.p2.x - self.p1.x) * (self.p2.x - self.p1.x) + (self.p2.y - self.p1.y) * (self.p2.y - self.p1.y))
        b = sqrt((self.p3.x - self.p2.x) * (self.p3.x - self.p2.x) + (self.p3.y - self.p2.y) * (self.p3.y - self.p2.y))
        c = sqrt((self.p3.x - self.p1.x) * (self.p3.x - self.p1.x) + (self.p3.y - self.p1.y) * (self.p3.y - self.p1.y))

        if c > a + b or b > a + c or a > b + c:
            return 0

        if fabs(a + b - c) < eps or fabs(a + c - b) < eps or fabs(b + c - a) < eps:
            return 0

        return 1

    def point_position(self, p):
        '''
        :param p: point
        :return: 1 - inside, 0 - on, -1 - outside
        '''
        eps = 1e-6

        v1 = (self.p1.x - p.x) * (self.p2.y - self.p1.y) - (self.p2.x - self.p1.x) * (self.p1.y - p.y)
        v2 = (self.p2.x - p.x) * (self.p3.y - self.p2.y) - (self.p3.x - self.p2.x) * (self.p2.y - p.y)
        v3 = (self.p3.x - p.x) * (self.p1.y - self.p3.y) - (self.p1.x - self.p3.x) * (self.p3.y - p.y)

        if fabs(v1) < eps or fabs(v2) < eps or fabs(v3) < eps:
            return 0

        if (v1 < 0 and v2 < 0 and v3 < 0) or (v1 > 0 and v2 > 0 and v3 > 0):
            return 1

        return -1


class Circle():
    def __init__(self, p1, p2, p3):
        self.c, self.r = self.create_from_points(p1, p2, p3)

    def create_from_points(self, p1, p2, p3):
        x12 = p1.x - p2.x
        x23 = p2.x - p3.x
        x31 = p3.x - p1.x
        y12 = p1.y - p2.y
        y23 = p2.y - p3.y
        y31 = p3.y - p1.y
        k1 = p1.x * p1.x + p1.y * p1.y
        k2 = p2.x * p2.x + p2.y * p2.y
        k3 = p3.x * p3.x + p3.y * p3.y

        x = - (y12 * k3 + y23 * k1 + y31 * k2) / (2 * (x12 * y31 - y12 * x31))
        y = (x12 * k3 + x23 * k1 + x31 * k2) / (2 * (x12 * y31 - y12 * x31))

        c = Point(x, y)
        r = sqrt((p1.x - x) * (p1.x - x) + (p1.y - y) * (p1.y - y))

        return c, r

    def point_position(self, p):
        '''
        :param p: point
        :return: 1 - inside, 0 - on, -1 - outside
        '''
        eps = 1e-6

        l = sqrt((p.x - self.c.x) * (p.x - self.c.x) + (p.y - self.c.y) * (p.y - self.c.y))

        if l < self.r:
            return 1

        if fabs(l - self.r) < eps:
            return 0

        return -1


class Points():
    def __init__(self, points, canvas, offset):
        self.points = points
        self.res_circle = None
        self.res_triangle = None
        self.canvas = canvas
        self.offset = offset

    def draw_res(self):
        p_nums, self.res_circle, self.res_triangle = self.find_points()
        if self.res_circle is None:
            raise NoTriangleException
        points_converted, xc, yc = self.converted_points()

        self.canvas.draw_triangle(self.res_triangle.p1.x, self.res_triangle.p1.y,
                                  self.res_triangle.p2.x, self.res_triangle.p2.y,
                                  self.res_triangle.p3.x, self.res_triangle.p3.y, (255, 0, 0), 3)

        self.canvas.draw_circle(self.res_circle.c.x, self.res_circle.c.y, self.res_circle.r, (255, 0, 0), 3)

        for point in points_converted:
            if point.num in p_nums:
                color = (0, 255, 0)
            else:
                color = (255, 255, 0)

            self.canvas.draw_point(point.x, point.y, point.x_draw, point.y_draw, point.num, color, 5)

        if 0 < xc < self.canvas.width():
            self.canvas.draw_arrow(xc, self.canvas.height(), xc, 0, -5, 10, 5, 10, (255, 0, 255), 2)

        if 0 < yc < self.canvas.height():
            self.canvas.draw_arrow(0, yc, self.canvas.width(), yc, -10, 5, -10, -5, (255, 0, 255), 2)


    def converted_points(self):
        xmin = self.res_circle.c.x - self.res_circle.r
        xmax = self.res_circle.c.x + self.res_circle.r
        ymin = self.res_circle.c.y - self.res_circle.r
        ymax = self.res_circle.c.y + self.res_circle.r
        for point in self.points:
            if xmin > point.x:
                xmin = point.x
            if xmax < point.x:
                xmax = point.x
            if ymin > point.y:
                ymin = point.y
            if ymax < point.y:
                ymax = point.y

#        ky = (self.canvas.height() * (1 - self.offset * 2)) / (ymax - ymin)
#        kx = (self.canvas.width() * (1 - self.offset * 2)) / (xmax - xmin)
#
#        yc = self.canvas.height() * self.offset + ymax * ky
#        xc = self.canvas.width() * self.offset - xmin * kx
#
#        points_converted = self.points.copy()
#        for point in points_converted:
#            point.convert_to_draw(xc, yc, kx, ky)
#
#        self.res_circle.c.convert_to_draw(xc, yc, kx, ky)
#
#        return points_converted, xc, yc

        ky = (self.canvas.height() * (1 - self.offset * 2)) / (ymax - ymin)
        kx = (self.canvas.width() * (1 - self.offset * 2)) / (xmax - xmin)

        yc = self.canvas.height() * self.offset + ymax * ky
        xc = self.canvas.width() * self.offset - xmin * kx

        k = min(ky, kx)

        points_converted = self.points.copy()
        for point in points_converted:
            point.convert_to_draw(xc, yc, k)

        self.res_circle.c.convert_to_draw(xc, yc, k)
        self.res_circle.r *= k

        return points_converted, xc, yc

    def find_points(self):
        p_nums = [0, 0, 0]
        circle = None
        triangle = None
        p_diff = len(self.points)

        for i in range(len(self.points) - 2):
            for j in range(i + 1, len(self.points) - 1):
                for k in range(j + 1, len(self.points)):
                    p_cur_nums = [i + 1, j + 1, k + 1]
                    t = Triangle(self.points[i], self.points[j], self.points[k])
                    if not t.is_correct():
                        continue

                    c = Circle(self.points[i], self.points[j], self.points[k])

                    p_in_tr = 0
                    p_in_c = 0

                    for point in self.points:
                        if point.num in p_cur_nums:
                            continue

                        tpos = t.point_position(point)
                        if tpos == 1:
                            p_in_tr += 1
                        elif tpos == -1 and c.point_position(point) == 1:
                            p_in_c += 1

                    if p_in_tr - p_in_c < p_diff:
                        p_diff = p_in_tr - p_in_c
                        p_nums = p_cur_nums.copy()
                        circle = c
                        triangle = t

        return p_nums, circle, triangle