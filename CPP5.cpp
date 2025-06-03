#include <iostream>
#include <vector>
#include <random>
#include <cstdint>
#include <string>

using namespace std;

using StrategyFunc = bool(*)(int32_t, const vector<bool>&, const vector<bool>&);

bool alwaysCooperate(int32_t /*round*/, const vector<bool>& /*self*/, const vector<bool>& /*enemy*/) {
    return true;
}

bool alwaysBetray(int32_t /*round*/, const vector<bool>& /*self*/, const vector<bool>& /*enemy*/) {
    return false;
}

bool titForTat(int32_t round, const vector<bool>& /*self*/, const vector<bool>& enemy) {
    if (round == 0) return true;
    return enemy[round - 1];
}

struct Result {
    string nameA;
    string nameB;
    int rounds = 0;
    int scoreA = 0;
    int scoreB = 0;
    int winner = 0;
};

Result playGame(StrategyFunc algoA, StrategyFunc algoB, const string& nameA, const string& nameB) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100, 200);
    int rounds = dist(gen);

    vector<bool> choicesA;
    vector<bool> choicesB;

    int scoreA = 0;
    int scoreB = 0;

    for (int32_t round = 0; round < rounds; ++round) {
        bool choiceA = algoA(round, choicesA, choicesB);
        bool choiceB = algoB(round, choicesB, choicesA);

        choicesA.push_back(choiceA);
        choicesB.push_back(choiceB);

        if (!choiceA && !choiceB) {
            scoreA += 4;
            scoreB += 4;
        }
        else if (!choiceA && choiceB) {
            scoreA += 20;
            scoreB += 0;
        }
        else if (choiceA && !choiceB) {
            scoreA += 0;
            scoreB += 20;
        }
        else {
            scoreA += 24;
            scoreB += 24;
        }
    }

    int winner = 0;
    if (scoreA > scoreB) winner = 1;
    else if (scoreB > scoreA) winner = 2;

    return Result{ nameA, nameB, rounds, scoreA, scoreB, winner };
}

void printResult(const Result& res) {
    cout << res.nameA << " против " << res.nameB << "\n";
    if (res.nameA == "Зеркальный" && res.nameB == "Всегда предаёт")
        cout << "Раундов: " << res.rounds << "\n";
    else
        cout << "Раундов сыграно : " << res.rounds << "\n";
    cout << res.nameA << " набрал : " << res.scoreA << " очков\n";
    cout << res.nameB << " набрал : " << res.scoreB << " очков\n";

    if (res.winner == 1)
        cout << "Победил : " << res.nameA << "\n";
    else if (res.winner == 2)
        cout << "Победил : " << res.nameB << "\n";
    else
        cout << "Ничья\n";

    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    const string nameAlwaysCooperate = "Всегда сотрудничает";
    const string nameAlwaysBetray = "Всегда предаёт";
    const string nameTitForTat = "Зеркальный";

    vector<Result> results;
    results.push_back(playGame(alwaysCooperate, alwaysBetray, nameAlwaysCooperate, nameAlwaysBetray));
    results.push_back(playGame(alwaysCooperate, titForTat, nameAlwaysCooperate, nameTitForTat));
    results.push_back(playGame(titForTat, alwaysBetray, nameTitForTat, nameAlwaysBetray));

    for (const auto& r : results) {
        printResult(r);
    }

    int winsAlwaysCooperate = 0, winsAlwaysBetray = 0, winsTitForTat = 0;
    for (const auto& r : results) {
        if (r.winner == 1) {
            if (r.nameA == nameAlwaysCooperate) winsAlwaysCooperate++;
            else if (r.nameA == nameAlwaysBetray) winsAlwaysBetray++;
            else if (r.nameA == nameTitForTat) winsTitForTat++;
        }
        else if (r.winner == 2) {
            if (r.nameB == nameAlwaysCooperate) winsAlwaysCooperate++;
            else if (r.nameB == nameAlwaysBetray) winsAlwaysBetray++;
            else if (r.nameB == nameTitForTat) winsTitForTat++;
        }
    }

    string bestAlgorithm;
    if (winsTitForTat >= winsAlwaysCooperate && winsTitForTat >= winsAlwaysBetray) {
        bestAlgorithm = nameTitForTat;
    }
    else if (winsAlwaysCooperate >= winsTitForTat && winsAlwaysCooperate >= winsAlwaysBetray) {
        bestAlgorithm = nameAlwaysCooperate;
    }
    else {
        bestAlgorithm = nameAlwaysBetray;
    }

    cout << "Лучший алгоритм: " << bestAlgorithm << "\n";

    return 0;
}
