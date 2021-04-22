def xx_scalar(table, pow1, pow2):
    res = 0
    for i in range(len(table)):
        res += table[i][2] * (table[i][0] ** (pow1 + pow2))
    
    return res

def yx_scalar(table, y_pow, x_pow):
    res = 0
    for i in range(len(table)):
        res += table[i][2] * (table[i][1] ** y_pow) * (table[i][0] ** x_pow)
    
    return res

def gen_slau(table, n):
    slau = []

    for k in range(n + 1):
        row = []
        for m in range(n + 1):
            row.append(xx_scalar(table, k, m))
        row.append(yx_scalar(table, 1, k))
        slau.append(row)
    
    return slau

def solve_slau(slau):
    for i in range(len(slau)):
        tmp = slau[i][i]
        for j in range(len(slau[0])):
            slau[i][j] /= tmp
        
        for j in range(i + 1, len(slau)):
            tmp = slau[j][i]
            for k in range(len(slau[0])):
                slau[j][k] -= slau[i][k] * tmp
    
    coefs = []

    for i in range(len(slau) - 1, -1, -1):
        coef = slau[i][len(slau[0]) - 1]

        for j in range(len(coefs)):
            coef -= coefs[j] * slau[i][i + j + 1]
        
        coefs.insert(0, coef)
    
    return coefs

def find_dots(coefs, start, end, step):
    dots = []

    x = start

    while x <= end:
        y = 0
        for i in range(len(coefs)):
            y += coefs[i] * (x ** i)
        
        dots.append((x, y))

        x += step
    
    return dots



def squares_method(table, n):
    slau = gen_slau(table, n)
        
    coefs = solve_slau(slau)

    return find_dots(coefs, table[0][0], table[len(table) - 1][0], 0.01)