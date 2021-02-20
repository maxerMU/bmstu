from newton import Newton_polynom
from hermit import Hermit_polynom

table = [[0.00, 1.000000, -1.000000],
         [0.15, 0.838771, -1.14944],
         [0.30, 0.655336, -1.29552],
         [0.45, 0.450447, -1.43497],
         [0.60, 0.225336, -1.56464],
         [0.75, -0.018310, -1.68164],
         [0.90, -0.278390, -1.78333],
         [1.05, -0.552430, -1.86742]]

def find_root(n):
    table_revert = [(x[1], x[0]) for x in table]
    newton = Newton_polynom(table_revert, n, 0)
    newton.find_polynom()

    return newton.res(0)


def main():
    print("x = 0.525")
    print("| power | " + " " * 4 + "Newton | " + " " * 4 + "Hermit |")
    for n in range(1, 5):
        newton = Newton_polynom(table, n, 0.525)
        newton.find_polynom()
        yn = newton.res(0.525)

        hermit = Hermit_polynom(table, n, 0.525)
        hermit.find_polynom()
        yh = hermit.res(0.525)

        print(f"| {n:5} | {yn:10.8} | {yh:10.8} |")
        print()

    print("| power | " + " " * 6 + "root |")
    for n in range(1, 5):
        root = find_root(n)
        print(f"| {n:5} | {root:10.8} |")

    n = int(input("Input polynom power: "))
    arg = float(input("Input argument: "))
    x = float(input("Input argument: "))

    newton = Newton_polynom(table, n, arg)
    newton.find_polynom()
    yn = newton.res(x)

    hermit = Hermit_polynom(table, n, arg)
    hermit.find_polynom()
    yh = hermit.res(x)

    print(f"Newton res - {yn:.8}")
    print(f"Hermit res - {yh:.8}")

if __name__ == "__main__":
    main()