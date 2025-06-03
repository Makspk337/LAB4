#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const double EPSILON = 1e-4;
const int MAX_ITER = 100;
const double STEP = 0.1;

double f(double x) {
    return cos(x + 0.5) - x - 2;
}

double f_derivative(double x) {
    return -sin(x + 0.5) - 1;
}

double phi(double x) {
    return cos(x + 0.5) - 2;
}

double bisection(double a, double b, int& iterations) {
    iterations = 0;
    double mid;
    cout << "\n--Метод половинного деления на [" << a << "," << b << "]--\n";
    cout << "N       a               b           b - a\n";
    cout << "--------------------------------------------\n";

    while ((b - a) > EPSILON && iterations < MAX_ITER) {
        mid = (a + b) / 2.0;
        cout << setw(2) << iterations + 1 << "  " << setw(4) << fixed << setprecision(6) << a << "  " << setw(14) << b << "  " << setw(12) << b - a << "\n";

        if (f(a) * f(mid) < 0)
            b = mid;
        else
            a = mid;

        iterations++;
    }
    return (a + b) / 2.0;
}

double newton(double x0, int& iterations) {
    iterations = 0;
    double x1;
    cout << "\n--------Метод Ньютона (x0 = " << fixed << setprecision(6) << x0 << ")--------\n";
    cout << "N      x_n           x_{n+1}     |x_{n+1}-x_n|\n";
    cout << "----------------------------------------------\n";

    while (iterations < MAX_ITER) {
        double fx = f(x0);
        double dfx = f_derivative(x0);

        if (fabs(dfx) < 1e-10) {
            cout << "Производная близка к нулю. Метод Ньютона не применим.\n";
            return x0;
        }

        x1 = x0 - fx / dfx;
        cout << setw(2) << iterations + 1 << "  " << setw(4) << x0 << "  " << setw(14) << x1 << "  " << setw(14) << fabs(x1 - x0) << "\n";

        if (fabs(x1 - x0) < EPSILON)
            break;

        x0 = x1;
        iterations++;
    }
    return x1;
}

double simple_iteration(double x0, int& iterations) {
    iterations = 0;
    double x1;

    cout << "\n---Метод простых итераций (x0 = " << fixed << setprecision(6) << x0 << ")---\n";
    cout << "N       x_n          x_{n+1}    |x_{n+1}-x_n|\n";
    cout << "---------------------------------------------\n";

    while (iterations < MAX_ITER) {
        x1 = phi(x0);

        cout << setw(2) << iterations + 1 << "  " << setw(4) << x0 << "  " << setw(14) << x1 << "  " << setw(14) << fabs(x1 - x0) << "\n";

        if (fabs(x1 - x0) < EPSILON)
            break;

        x0 = x1;
        iterations++;

        if (iterations >= MAX_ITER) {
            cout << "Метод простых итераций не сошелся за " << MAX_ITER << " итераций\n";
            break;
        }
    }
    return x1;
}

vector<pair<double, double>> find_root_intervals(double start, double end, double step) {
    vector<pair<double, double>> intervals;
    double x1 = start;
    double x2 = x1 + step;

    while (x2 <= end) {
        if (f(x1) * f(x2) < 0)
            intervals.emplace_back(x1, x2);
        x1 = x2;
        x2 += step;
    }
    return intervals;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Уравнение: cos(x + 0.5) - x = 2\n";

    auto intervals = find_root_intervals(-5, 5, STEP);
    cout << "Найдено " << intervals.size() << " интервал(ов) с корнем: ";
    for (auto& p : intervals)
        cout << " [" << p.first << ", " << p.second << "]\n";

    int root_num = 1;
    for (auto& interval : intervals) {
        int b_iter = 0;
        int n_iter = 0;
        int s_iter = 0;

        cout << "\n-------- Корень " << root_num++ << " в [" << interval.first << ", " << interval.second << "] --------\n";

        double b_root = bisection(interval.first, interval.second, b_iter);
        cout << "\nПоловинное деление: x* = " << b_root << " (итераций = " << b_iter << ")\n";

        double midpoint = (interval.first + interval.second) / 2.0;
        double n_root = newton(midpoint, n_iter);
        cout << "Ньютон: x* = " << n_root << " (итераций = " << n_iter << ")\n";

        double s_root = simple_iteration(midpoint, s_iter);
        cout << "Простые итерации: x* = " << s_root << " (итераций = " << s_iter << ")\n";
    }

    return 0;
}
