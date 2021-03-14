from newton import Newton_polynom

table_xy = [[0, 1, 2, 3, 4], [0, 1, 2, 3, 4]]
table_z = [[0, 1, 4, 9, 16],
           [1, 2, 5, 10, 17],
           [4, 5, 8, 13, 20],
           [9, 10, 13, 18, 25],
           [16, 17, 20, 25, 32]]


def three_d_inter(nx, ny, x_arg, y_arg):
    y_inter_table = []
    for i in range(len(table_xy[0])):
        table = [[table_xy[0][j], table_z[i][j]] for j in range(len(table_xy[0]))]
        np = Newton_polynom(table, nx, x_arg)
        np.find_polynom()
        y_inter_table.append(np.res(x_arg))

    table = [[table_xy[1][j], y_inter_table[j]] for j in range(len(table_xy[0]))]
    np = Newton_polynom(table, ny, y_arg)
    np.find_polynom()

    return np.res(y_arg)


def main():
    print("x = 1.5")
    print("y = 1.5")

    print("| power | interpolation result |")

    for power in range(1, 4):
        res = three_d_inter(power, power, 1.5, 1.5)

        print(f"| {power:5} | {res:20.8} |")


if __name__ == "__main__":
    main()
