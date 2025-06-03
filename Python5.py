import random
from typing import List, Callable, NamedTuple

StrategyFunc = Callable[[int, List[bool], List[bool]], bool]

def always_cooperate(round: int, self_history: List[bool], enemy_history: List[bool]) -> bool:
    return True

def always_betray(round: int, self_history: List[bool], enemy_history: List[bool]) -> bool:
    return False

def tit_for_tat(round: int, self_history: List[bool], enemy_history: List[bool]) -> bool:
    if round == 0:
        return True
    return enemy_history[round - 1]

class Result(NamedTuple):
    nameA: str
    nameB: str
    rounds: int
    scoreA: int
    scoreB: int
    winner: int  # 0 = ничья, 1 = A, 2 = B

def play_game(algoA: StrategyFunc, algoB: StrategyFunc, nameA: str, nameB: str) -> Result:
    rounds = random.randint(100, 200)
    choicesA: List[bool] = []
    choicesB: List[bool] = []
    scoreA = 0
    scoreB = 0

    for round in range(rounds):
        choiceA = algoA(round, choicesA, choicesB)
        choiceB = algoB(round, choicesB, choicesA)
        choicesA.append(choiceA)
        choicesB.append(choiceB)

        if not choiceA and not choiceB:
            scoreA += 4
            scoreB += 4
        elif not choiceA and choiceB:
            scoreA += 20
            scoreB += 0
        elif choiceA and not choiceB:
            scoreA += 0
            scoreB += 20
        else:  # choiceA and choiceB
            scoreA += 24
            scoreB += 24

    if scoreA > scoreB:
        winner = 1
    elif scoreB > scoreA:
        winner = 2
    else:
        winner = 0

    return Result(nameA, nameB, rounds, scoreA, scoreB, winner)

def print_result(res: Result):
    print(f"{res.nameA} против {res.nameB}")
    if res.nameA == "Зеркальный" and res.nameB == "Всегда предаёт":
        print(f"Раундов: {res.rounds}")
    else:
        print(f"Раундов сыграно : {res.rounds}")
    print(f"{res.nameA} набрал : {res.scoreA} очков")
    print(f"{res.nameB} набрал : {res.scoreB} очков")

    if res.winner == 1:
        print(f"Победил : {res.nameA}")
    elif res.winner == 2:
        print(f"Победил : {res.nameB}")
    else:
        print("Ничья")
    print()

nameAlwaysCooperate = "Всегда сотрудничает"
nameAlwaysBetray = "Всегда предаёт"
nameTitForTat = "Зеркальный"

results = [
    play_game(always_cooperate, always_betray, nameAlwaysCooperate, nameAlwaysBetray),
    play_game(always_cooperate, tit_for_tat, nameAlwaysCooperate, nameTitForTat),
    play_game(tit_for_tat, always_betray, nameTitForTat, nameAlwaysBetray),
]

for r in results:
    print_result(r)

winsAlwaysCooperate = 0
winsAlwaysBetray = 0
winsTitForTat = 0

for r in results:
    if r.winner == 1:
        if r.nameA == nameAlwaysCooperate:
            winsAlwaysCooperate += 1
        elif r.nameA == nameAlwaysBetray:
            winsAlwaysBetray += 1
        elif r.nameA == nameTitForTat:
            winsTitForTat += 1
    elif r.winner == 2:
        if r.nameB == nameAlwaysCooperate:
            winsAlwaysCooperate += 1
        elif r.nameB == nameAlwaysBetray:
            winsAlwaysBetray += 1
        elif r.nameB == nameTitForTat:
            winsTitForTat += 1

if winsTitForTat >= winsAlwaysCooperate and winsTitForTat >= winsAlwaysBetray:
    bestAlgorithm = nameTitForTat
elif winsAlwaysCooperate >= winsTitForTat and winsAlwaysCooperate >= winsAlwaysBetray:
    bestAlgorithm = nameAlwaysCooperate
else:
    bestAlgorithm = nameAlwaysBetray

print(f"Лучший алгоритм: {bestAlgorithm}")
