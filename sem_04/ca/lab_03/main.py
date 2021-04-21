from newton import Newton_polynom
from spline import Spline

def print_table(table):
    print('|  x  |  y  |')
    for row in table:
        print(f"|{row[0]:5}|{row[1]:5}|")

def main():
    table = [(x, x * x) for x in range(11)]

    print("таблица значений")
    print_table(table)

    x = float(input("Х = "))
    print(f"Точное значение: {x * x}")

    np = Newton_polynom(table, 3, x)
    np.find_polynom()
    print(f"Значение интерполяции полиномом Ньютона 3 степени {np.res(x)}")

    sp = Spline(table, x)
    sp.find_coefs()
    print(f"Интерполяция сплайном - {sp.res()}")


if __name__ == "__main__":
    main()
