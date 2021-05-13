import matplotlib.pyplot as plt
from math import sin, cos, pi, exp
from gauss import gauss
from simpson import simpson

def tao_func(tao):
    sub_func = lambda phi, teta: 2 * cos(teta) / (1 - sin(teta) * sin(teta) * cos(phi) * cos(phi))
    return lambda phi, teta: 4 / pi * (1 - exp(-tao * sub_func(phi, teta))) * cos(teta) * sin(teta)

def func_2_to_1(func, value):
    return lambda y: func(value, y)

def double_integreation(double_func, limits, nodes_counts, integreate_funcs):
    F = lambda y: integreate_funcs[1](func_2_to_1(double_func, y), limits[1][0], 
                                      limits[1][1], nodes_counts[1])
    return integreate_funcs[0](F, limits[0][0], limits[0][1], nodes_counts[0])

def plot_graphic(integr_func, tao_start, tao_end, tao_step, label):
    plt.figure(1)

    x = []
    tao = tao_start
    while tao <= tao_end:
        x.append(tao)
        tao += tao_step
    
    plt.plot(x, [integr_func(tao) for tao in x], label=label)

    plt.xlabel("tao")
    plt.ylabel("Intergreation")
    plt.grid(True)
    plt.legend(loc=0)

def gen_label(func1, func2, N, M):
    label = ""
    if (func1 == gauss):
        label += "ext - gauss\n"
    else:
        label += "ext - simpson\n"
    if (func2 == gauss):
        label += "int - gauss\n"
    else:
        label += "int - simpson\n"
    
    label += f"ext nodes - {N}\nint nodes - {M}"

    return label

def test_simpson():
    func1 = gauss
    func2 = simpson

    int_func1 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [10, 9], [func1, func2])
    int_func2 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [10, 3], [func1, func2])
    int_func3 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [9, 10], [func2, func1])
    int_func4 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [3, 10], [func2, func1])

    plot_graphic(int_func1, 0.05, 10, 0.05, gen_label(func1, func2, 10, 9))
    plot_graphic(int_func2, 0.05, 10, 0.05, gen_label(func1, func2, 10, 3))
    plot_graphic(int_func3, 0.05, 10, 0.05, gen_label(func2, func1, 9, 10))
    plot_graphic(int_func4, 0.05, 10, 0.05, gen_label(func2, func1, 3, 10))

def test_gauss():
    func1 = gauss
    func2 = simpson

    int_func1 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [3, 9], [func1, func2])
    int_func2 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [10, 9], [func1, func2])
    int_func3 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [9, 3], [func2, func1])
    int_func4 = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [9, 10], [func2, func1])

    plot_graphic(int_func1, 0.05, 10, 0.05, gen_label(func1, func2, 3, 9))
    plot_graphic(int_func2, 0.05, 10, 0.05, gen_label(func1, func2, 10, 9))
    plot_graphic(int_func3, 0.05, 10, 0.05, gen_label(func2, func1, 9, 3))
    plot_graphic(int_func4, 0.05, 10, 0.05, gen_label(func2, func1, 9, 10))

def main():
    tao = float(input("Input tao: "))
    N = int(input("Input N: "))
    M = int(input("Input M: "))

    method_select = bool(int(input("select external method (0 - simpson, 1 - gauss): ")))
    func1 = gauss if method_select else simpson
    method_select = bool(int(input("select internal method (0 - simpson, 1 - gauss): ")))
    func2 = gauss if method_select else simpson

    integr_func = lambda tao: double_integreation(tao_func(tao), [[0, pi/2], [0, pi/2]], [N, M], [func1, func2])
    print(f"Integreation res: {integr_func(tao)}")

    test = int(input("select test (0 - no test, 1 - simpson, 2 - gauss): "))
    if test == 0:
        plot_graphic(integr_func, 0.05, 10, 0.01, gen_label(func1, func2, N, M))
    elif test == 1:
        test_simpson()
    elif test == 2:
        test_gauss()

    plt.show()

if __name__ == "__main__":
    main()