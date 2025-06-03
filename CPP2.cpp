#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

double generate_random(minstd_rand0 &gen) {
    uniform_real_distribution<double> dist(-250.0, 250.0);
    return dist(gen);
}

void print_array(const vector<double> &arr) {
    for (double val : arr) {
        cout << fixed << setprecision(2) << val << " ";
    }
    cout << endl;
}

void shift_right(vector<double> &arr) {
    if (arr.empty()) return;
    double last = arr.back();
    for (int i = arr.size() - 1; i > 0; --i) {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
}

int main() {
    setlocale(LC_ALL, "rus");
    const size_t n = 20;
    minstd_rand0 gen(random_device{}());

    vector<double> array(n);
    for (double& val : array) {
        val = generate_random(gen);
    }

    cout << "Исходный массив:\n";
    print_array(array);

    int negative_count = 0;
    size_t min_abs_index = 0;
    double min_abs_value = abs(array[0]);

    for (size_t i = 0; i < array.size(); ++i) {
        if (array[i] < 0) {
            ++negative_count;
        }
        if (abs(array[i]) < min_abs_value) {
            min_abs_value = abs(array[i]);
            min_abs_index = i;
        }
    }

    double sum_after_min_abs = 0.0;
    for (size_t i = min_abs_index + 1; i < array.size(); ++i) {
        sum_after_min_abs += abs(array[i]);
    }

    cout << "\nКоличество отрицательных элементов: " << negative_count << endl;
    cout << "Сумма модулей после минимального по модулю элемента: " << sum_after_min_abs << endl;

    size_t max_len = 1, current_len = 1;
    size_t start_index = 0, end_index = 0, temp_start = 0;

    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i] < array[i - 1]) {
            ++current_len;
            if (current_len > max_len) {
                max_len = current_len;
                start_index = temp_start;
                end_index = i;
            }
        }
        else {
            current_len = 1;
            temp_start = i;
        }
    }

    cout << "\nСамая длинная убывающая последовательность:\n";
    for (size_t i = start_index; i <= end_index; ++i) {
        cout << fixed << setprecision(2) << array[i] << " ";
    }
    cout << "\nИндексы: от " << start_index << " до " << end_index << endl;

    max_len = 1; current_len = 1;
    start_index = end_index = temp_start = 0;

    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i] > array[i - 1]) {
            ++current_len;
            if (current_len > max_len) {
                max_len = current_len;
                start_index = temp_start;
                end_index = i;
            }
        }
        else {
            current_len = 1;
            temp_start = i;
        }
    }

    vector<double> reversed_inc_seq;
    for (size_t i = end_index + 1; i-- > start_index;) {
        reversed_inc_seq.push_back(array[i]);
    }

    cout << "\nНовая последовательность (обратная возрастающей):\n";
    print_array(reversed_inc_seq);

    vector<double> arr1 = { 1, 2, 3, 4, 5 };
    vector<double> arr2 = { 1, 2, 3 };

    shift_right(arr1);
    shift_right(arr2);

    cout << "\nПосле синхронного циклического сдвига:\n";
    cout << "Массив 1: "; print_array(arr1);
    cout << "Массив 2: "; print_array(arr2);

    return 0;
}
