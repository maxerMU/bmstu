from math import fabs, ceil


class Hermit_polynom:
    def __init__(self, table, power, arg):
        self.power = power
        self.arg = arg
        self.table = table.copy()
        self.diff = []

    def find_interval(self):
        self.table.sort(key=lambda x: fabs(x[0] - self.arg))
        for i in range(len(self.table) - 1, -1, -1):
            self.table.insert(i + 1, self.table[i])

    def find_diff(self):
        eps = 1e-6

        self.diff.append([x[1] for x in self.table])
        for i in range(self.power - 1, -1, -1):
            diff = []
            for j in range(0, i + 1):
                if fabs(self.table[j][0] - self.table[j + self.power - i][0]) < eps:
                    x = self.table[j + 1][2]
                else:
                    x = (self.diff[-1][j] - self.diff[-1][j + 1]) / \
                        (self.table[j][0] - self.table[j + self.power - i][0])
                diff.append(x)
            self.diff.append(diff)

    def find_polynom(self):
        self.find_interval()
        self.find_diff()

    def res(self, x):
        y = self.diff[0][0]
        for k in range(1, self.power + 1):
            xmlt = 1
            for j in range(0, k):
                xmlt *= (x - self.table[j][0])
            y += xmlt * (self.diff[k][0])

        return y