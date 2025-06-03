import random

n = 20
random.seed()
array = [random.uniform(-250, 250) for _ in range(n)]

print("Исходный массив:")
print(" ".join(f"{x:.2f}" for x in array))

negative_count = sum(1 for x in array if x < 0)

min_abs_index = min(range(n), key=lambda i: abs(array[i]))
sum_after_min_abs = sum(abs(x) for x in array[min_abs_index + 1:])

print(f"\nКоличество отрицательных элементов: {negative_count}")
print(f"Сумма модулей после минимального по модулю элемента: {sum_after_min_abs:.2f}")

max_len = 1
current_len = 1
start_index = 0
end_index = 0
temp_start = 0

for i in range(1, n):
    if array[i] < array[i - 1]:
        current_len += 1
        if current_len > max_len:
            max_len = current_len
            start_index = temp_start
            end_index = i
    else:
        current_len = 1
        temp_start = i

print("\nСамая длинная убывающая последовательность:")
print(" ".join(f"{x:.2f}" for x in array[start_index:end_index + 1]))
print(f"Индексы: от {start_index} до {end_index}")

max_len = 1
current_len = 1
start_index = 0
end_index = 0
temp_start = 0

for i in range(1, n):
    if array[i] > array[i - 1]:
        current_len += 1
        if current_len > max_len:
            max_len = current_len
            start_index = temp_start
            end_index = i
    else:
        current_len = 1
        temp_start = i

reversed_inc_seq = list(reversed(array[start_index:end_index + 1]))

print("\nНовая последовательность (обратная возрастающей):")
print(" ".join(f"{x:.2f}" for x in reversed_inc_seq))

arr1 = [1, 2, 3, 4, 5]
arr2 = [1, 2, 3]

def shift_right(arr):
    if arr:
        last = arr[-1]
        for i in reversed(range(1, len(arr))):
            arr[i] = arr[i - 1]
        arr[0] = last

shift_right(arr1)
shift_right(arr2)

print("\nПосле синхронного циклического сдвига:")
print("Массив 1:", arr1)
print("Массив 2:", arr2)
