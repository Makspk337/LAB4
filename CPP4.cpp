#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    int n, k;
    cout << "Введите число кандидатов и избирателей: ";
    cin >> n >> k;
    cin.ignore();

    vector<string> candidates(n);
    map<string, int> bordaScores;
    map<string, map<string, int>> condorcetMatrix;

    cout << "\nВведите имя кандидатов:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Кандидат №" << (i + 1) << ": ";
        getline(cin, candidates[i]);
        bordaScores[candidates[i]] = 0;
        for (const auto& other : candidates)
            condorcetMatrix[candidates[i]][other] = 0;
    }

    cout << "\nВведите голоса:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Голос " << i + 1 << ": ";
        vector<string> vote(n);
        for (string& name : vote)
            cin >> name;

        for (int j = 0; j < n; ++j) {
            bordaScores[vote[j]] += n - j - 1;
        }

        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                condorcetMatrix[vote[a]][vote[b]] += 1;
            }
        }
    }

    string bordaWinner;
    int maxScore = -1;
    for (const auto& pair : bordaScores) {
        const string& name = pair.first;
        int score = pair.second;
        if (score > maxScore) {
            maxScore = score;
            bordaWinner = name;
        }
    }

    string condorcetWinner;
    for (const auto& cand : candidates) {
        bool isWinner = true;
        for (const auto& other : candidates) {
            if (cand == other) continue;
            int win = condorcetMatrix[cand][other];
            int lose = condorcetMatrix[other][cand];
            if (win <= lose) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) {
            condorcetWinner = cand;
            break;
        }
    }

    cout << "\nМетодом Борда: Победил " << bordaWinner << " (" << maxScore << " баллов)\n";

    if (!condorcetWinner.empty()) {
        cout << "Методом Кондорсе: Победил " << condorcetWinner << "\n";
    }
    else {
        cout << "Методом Кондорсе: Победитель не определен (нет абсолютного победителя)\n";
    }

    if (bordaWinner != condorcetWinner && !condorcetWinner.empty()) {
        cout << "\nПримечание: Разные алгоритмы дали разные результаты. Это возможно из-за различий в критериях победы.\n";
    }

    return 0;
}
