print("Введите число кандидатов и избирателей: ", end="")
n, k = map(int, input().split())

candidates = []
borda_scores = {}
condorcet_matrix = {}

print("\nВведите имя кандидатов:")
for i in range(n):
    name = input(f"Кандидат №{i + 1}: ").strip()
    candidates.append(name)
    borda_scores[name] = 0
    condorcet_matrix[name] = {other: 0 for other in candidates}

for name in candidates:
    for other in candidates:
        condorcet_matrix[name].setdefault(other, 0)

print("\nВведите голоса:")
for i in range(k):
    print(f"Голос {i + 1}: ", end="")
    vote = input().split()

    for j, candidate_name in enumerate(vote):
        borda_scores[candidate_name] += n - j - 1

    for a in range(n):
        for b in range(a + 1, n):
            condorcet_matrix[vote[a]][vote[b]] += 1

borda_winner = max(borda_scores, key=borda_scores.get)
max_score = borda_scores[borda_winner]

condorcet_winner = None
for cand in candidates:
    is_winner = True
    for other in candidates:
        if cand == other:
            continue
        win = condorcet_matrix[cand][other]
        lose = condorcet_matrix[other][cand]
        if win <= lose:
            is_winner = False
            break
    if is_winner:
        condorcet_winner = cand
        break

print(f"\nМетодом Борда: Победил {borda_winner} ({max_score} баллов)")

if condorcet_winner:
    print(f"Методом Кондорсе: Победил {condorcet_winner}")
else:
    print("Методом Кондорсе: Победитель не определен (нет абсолютного победителя)")

if condorcet_winner and borda_winner != condorcet_winner:
    print("\nПримечание: Разные алгоритмы дали разные результаты. Это возможно из-за различий в критериях победы.")

