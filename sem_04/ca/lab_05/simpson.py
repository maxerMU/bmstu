def simpson(func, a, b, nodes_count):
    h = (b - a) / (nodes_count - 1)
    x = a
    res = 0

    for i in range((nodes_count - 1) // 2):
        res += func(x) + 4 * func(x + h) + func(x + 2 * h)
        x += 2 * h
    
    return h / 3 * res