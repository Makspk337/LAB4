import math

EPSILON = 1e-4
MAX_ITER = 100
STEP = 0.1

def f(x):
    return math.cos(x + 0.5) - x - 2

def f_derivative(x):
    return -math.sin(x + 0.5) - 1

def phi(x):
    return math.cos(x + 0.5) - 2

def bisection(a, b):
    iterations = 0
    print(f"\n--Метод половинного деления на [{a},{b}]--")
    print("N       a               b           b - a")
    print("--------------------------------------------")

    while (b - a) > EPSILON and iterations < MAX_ITER:
        mid = (a + b) / 2.0
        print(f"{iterations + 1:2}  {a:14.6f}  {b:14.6f}  {b - a:12.6f}")

        if f(a) * f(mid) < 0:
            b = mid
        else:
            a = mid
        iterations += 1

    return (a + b) / 2.0, iterations

def newton(x0):
    iterations = 0
    print(f"\n--------Метод Ньютона (x0 = {x0:.6f})--------")
    print("N      x_n           x_{n+1}     |x_{n+1}-x_n|")
    print("----------------------------------------------")

    while iterations < MAX_ITER:
        fx = f(x0)
        dfx = f_derivative(x0)

        if abs(dfx) < 1e-10:
            print("Производная близка к нулю. Метод Ньютона не применим.")
            return x0, iterations

        x1 = x0 - fx / dfx
        print(f"{iterations + 1:2}  {x0:14.6f}  {x1:14.6f}  {abs(x1 - x0):14.6f}")

        if abs(x1 - x0) < EPSILON:
            break

        x0 = x1
        iterations += 1

    return x1, iterations

def simple_iteration(x0):
    iterations = 0
    print(f"\n---Метод простых итераций (x0 = {x0:.6f})---")
    print("N       x_n          x_{n+1}    |x_{n+1}-x_n|")
    print("---------------------------------------------")

    while iterations < MAX_ITER:
        x1 = phi(x0)
        print(f"{iterations + 1:2}  {x0:14.6f}  {x1:14.6f}  {abs(x1 - x0):14.6f}")

        if abs(x1 - x0) < EPSILON:
            break

        x0 = x1
        iterations += 1

    else:
        print(f"Метод простых итераций не сошелся за {MAX_ITER} итераций")

    return x1, iterations

def find_root_intervals(start, end, step):
    intervals = []
    x1 = start
    x2 = x1 + step

    while x2 <= end:
        if f(x1) * f(x2) < 0:
            intervals.append((x1, x2))
        x1 = x2
        x2 += step

    return intervals


print("Уравнение: cos(x + 0.5) - x = 2")

intervals = find_root_intervals(-5, 5, STEP)
print(f"Найдено {len(intervals)} интервал(ов) с корнем:")
for interval in intervals:
    print(f" [{interval[0]}, {interval[1]}]")

root_num = 1
for interval in intervals:
    a, b = interval
    print(f"\n-------- Корень {root_num} в [{a}, {b}] --------")

    b_root, b_iter = bisection(a, b)
    print(f"\nПоловинное деление: x* = {b_root} (итераций = {b_iter})")

    midpoint = (a + b) / 2.0
    n_root, n_iter = newton(midpoint)
    print(f"Ньютон: x* = {n_root} (итераций = {n_iter})")

    s_root, s_iter = simple_iteration(midpoint)
    print(f"Простые итерации: x* = {s_root} (итераций = {s_iter})")

    root_num += 1
