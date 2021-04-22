import matplotlib.pyplot as plt
from squares_method import squares_method

def plot_graphs(table, pows):
    plt.figure(1)

    plt.scatter([dot[0] for dot in table], [dot[1] for dot in table], c = 'black', label = "data")

    for power in pows:
        dots = squares_method(table, power)
        plt.plot([dot[0] for dot in dots], [dot[1] for dot in dots], label = f"power = {power}")
    
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.legend(loc = 0)
    
    plt.show()

def print_table(table):
    print("|  №  |  X  |  Y  |  P  |")
    for i in range(len(table)):
        print(f"|{i : 5}|{table[i][0] : 5}|{table[i][1] : 5}|{table[i][2] : 5}|")

def change_point_weight(table):
    i = int(input("Input point number: "))
    weight = int(input("Input new point weight"))

    table[i][2] = weight

def main():
    table = [[0, 1, 1],
             [1, 1.5, 1],
             [2, 2, 1],
             [3, 0, 1],
             [4, -1, 1],
             [5, -2, 1],
             [6, -0.5, 1],
             [7, 1, 1],
             [8, 4, 1],
             [9, 7, 1]]
    
    choise = 10
    while (choise):
        print("1 - Print table\n" +
              "2 - Change point weight\n" +
              "3 - Plot graphs\n" +
              "0 - Exit")

        choise = int(input("Your choise: "))

        if choise == 1:
            print_table(table)
        elif choise == 2:
            change_point_weight(table)
        elif choise == 3:
            plot_graphs(table, [1, 2, 5, 6])

    

if __name__ == "__main__":
    main()