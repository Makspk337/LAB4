#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    int X0, A, B, C;
    cout << "Введите X0, A, B, C: ";
    cin >> X0 >> A >> B >> C;

    vector<int> sequence;
    unordered_map<int, int> seen;

    int X = X0;
    int repeatStartIndex = -1;

    while (true) {
        if (seen.count(X)) {
            repeatStartIndex = sequence.size();
            break;
        }
        seen[X] = sequence.size();
        sequence.push_back(X);
        X = (A * X + B) % C;
    }

    cout << "Последовательность: ";
    for (int i = 0; i < 10; ++i) {
        cout << sequence[i % sequence.size()] << " ";
    }
    cout << "\n";

    cout << "Повторение начинается с " << repeatStartIndex + 1 << " элемента" << std::endl;

    return 0;
}
