from math import fabs

def mul_polynoms(pol1, pol2):
    res_pol = [0 for i in range(len(pol1) + len(pol2) - 1)]

    for i in range(len(pol1)):
        for j in range(len(pol2)):
            res_pol[i + j] += pol1[i] * pol2[j]
    
    return res_pol

def diff_polynoms(pol1, pol2):
    max_len = max(len(pol1), len(pol2))
    res_pol = [0 for i in range(max_len)]

    for i in range(len(pol1)):
        res_pol[i + len(res_pol) - len(pol1)] += pol1[i]

    for i in range(len(pol2)):
        res_pol[i + len(res_pol) - len(pol2)] -= pol2[i]
    
    return res_pol

def polynom_value(pol, x):
    res = 0
    for i in range(len(pol)):
        res += pol[i] * (x ** (len(pol) - i - 1))
    
    return res

def find_legandr_pol(n):
    leg_pol_0 = [1] #1
    leg_pol_1 = [1, 0] #x

    prev = leg_pol_0
    res_pol = leg_pol_1

    for power in range(2, n + 1):
        coef_1 = [(2 * power - 1) / power, 0] #(2 ^ power - 1 / power) * x
        coef_2 = [(power - 1) / power] # (power - 1) / power
        mul_pol1 = mul_polynoms(coef_1, res_pol)
        mul_pol2 = mul_polynoms(coef_2, prev)
        tmp = [x for x in res_pol]
        res_pol = diff_polynoms(mul_polynoms(coef_1, res_pol), mul_polynoms(coef_2, prev))
        prev = [x for x in tmp]

    return res_pol

def half_mid_division(pol, left, right):
    mid = left + (right - left) / 2
    res = polynom_value(pol, mid)
    while fabs(res) > 1e-5:
        if res * polynom_value(pol, left) < 0:
            right = mid
        else:
            left = mid
        mid = left + (right - left) / 2
        res = polynom_value(pol, mid)

    return mid

def find_roots(leg_pol):
    n = len(leg_pol) - 1
    parts = 2 * n
    is_find_segments = False

    while (not is_find_segments):
        segments = []
        step = 2 / parts

        x = -1
        for i in range(parts - 1):
            if (polynom_value(leg_pol, x) * polynom_value(leg_pol, x + step) < 0 or
                polynom_value(leg_pol, x) == 0):
                segments.append([x, x + step])
            x += step
        if (polynom_value(leg_pol, x) * polynom_value(leg_pol, 1) < 0 or
            polynom_value(leg_pol, x) == 0):
            segments.append([x, 1])

        if len(segments) == n:
            is_find_segments = True

    return [half_mid_division(leg_pol, seg[0], seg[1]) for seg in segments]

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

def find_args(roots):
    mtr = []
    for i in range(len(roots)):
        row = [root ** i for root in roots]
        if i % 2 == 1:
            row.append(0)
        else:
            row.append(2 / (i + 1))
        mtr.append(row)
    
    return solve_slau(mtr)

def convert_arg(t, a, b):
    return (b - a) / 2 * t + (b + a) / 2

def gauss(func, a, b, node_count):
    leg_pol = find_legandr_pol(node_count)
    roots = find_roots(leg_pol)
    args = find_args(roots)

    res = 0
    for i in range(node_count):
        res += (b - a) / 2 * args[i] * func(convert_arg(roots[i], a, b))
    
    return res