def right(y, h, i):
    return (y[i + 1] - y[i]) / h if i < len(y) - 1 else ""

def center(y, h, i):
    return (y[i + 1] - y[i - 1]) / (2 * h) if i > 0 and i < len(y) - 1 else ""

def double_diff(y, h, i):
    return (y[i + 1] - 2 * y[i] + y[i - 1]) / (h * h) if i > 0 and i  <len(y) - 1 else ""

def right_double(y, h, i):
    return (y[i + 2] - y[i]) / h if i < len(y) - 2 else ""

def runge(y, h, i): # p == 1; m == 2
    if i >= len(y) - 2:
        return ""

    f2h = right_double(y, h, i)
    fh = right(y, h, i)

    return 2 * fh - f2h

def align_vars(y, x, i): #eta = 1 / y eps = 1 / x
    if i >= len(y) - 1:
        return ""

    eta_eps_dif = (1 / y[i + 1] - 1 / y[i]) / (1 / x[i + 1] - 1 / x[i])
    return eta_eps_dif * y[i] * y[i] / (x[i] * x[i])



def main():
    x = [1, 2, 3, 4, 5, 6]
    y = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]

    print("|  x  |   y   |    1    |    2    |    3    |    4    |    5    |")

    for i in range(len(x)):
        res_1 = right(y, 1, i)
        res_2 = center(y, 1, i)
        res_3 = runge(y, 1, i)
        res_4 = align_vars(y, x, i)
        res_5 = double_diff(y, 1, i)
        print(f"| {x[i]:3} | {y[i]:5} | {res_1:7.3} | {res_2:7.3} | {res_3:7.3} | {res_4:7.3} | {res_5:7.3} |")

if __name__ == "__main__":
    main()