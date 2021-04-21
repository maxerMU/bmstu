class Spline:
    def __init__(self, table, x):
        self.table = table
        self.x = x
        self.N = len(table) - 1
        self.a = [0]
        self.b = [0]
        self.d = [0]
        self.c = [0, 0]
        self.kci = [0, 0, 0]
        self.etta = [0, 0, 0]
        self.h = [0, table[1][0] - table[0][0]]

    def find_coefs(self):
        for i in range(2, self.N + 1):
            self.h.append(self.table[i][0] - self.table[i - 1][0])
            f = 3 * ((self.table[i][1] - self.table[i - 1][1]) / self.h[i] - (self.table[i - 1][1] - self.table[i - 2][1]) / self.h[i - 1])
            self.kci.append(-self.h[i] / (self.h[i - 1] * self.kci[i] + 2 * (self.h[i - 1] + self.h[i])))
            self.etta.append((f - self.h[i - 1] * self.etta[i]) / (self.h[i - 1] * self.kci[i] + 2 * (self.h[i - 1] + self.h[i])))

        for i in range(self.N - 1, 0, -1):
            self.c.insert(0, self.kci[i + 1] * self.c[0] + self.etta[i + 1])
        self.c.insert(0, 0)

        for i in range(1, self.N + 1):
            self.a.append(self.table[i - 1][1])
            self.b.append((self.table[i][1] - self.table[i - 1][1]) / self.h[i] - self.h[i] * (self.c[i + 1] + 2 * self.c[i]) / 3)
            self.d.append((self.c[i + 1] - self.c[i]) / (3 * self.h[i]))

    def res(self):
        pos = 0
        for i in range(0, self.N):
            if self.table[i][1] <= self.x and self.table[i + 1][1] >= self.x:
                pos = i + 1
                break

        return (self.a[pos] + self.b[pos] * (self.x - self.table[pos - 1][0]) + self.c[pos] * (self.x - self.table[pos - 1][0]) ** 2 + self.d[pos] * (
                    self.x - self.table[pos - 1][0]) ** 3)