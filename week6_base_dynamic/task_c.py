
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 22 22:32:03 2020

@author: Asus

https://codeforces.com/group/zJTwakJcKM/contest/299322/problem/C

C. Наибольшая возрастающая подпоследовательность
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Пусть a1, a2, ..., an — числовая последовательность. Длина последовательности — это количество элементов этой последовательности. Последовательность ai1, ai2, ..., aik называется подпоследовательностью последовательности a, если 1 ? i1 < i2 < ... < ik ? n. Последовательность a называется возрастающей, если a1 < a2 < ... < an.

Вам дана последовательность, содержащая n целых чисел. Найдите ее самую длинную возрастающую подпоследовательность.

Входные данные
В первой строке задано одно число n (1 ? n ? 2000) — длина подпоследовательности. В следующей строке задано n целых чисел ai ( - 109 ? ai ? 109) — элементы последовательности.

Выходные данные
В первой строке выведите число k — длину наибольшей возрастающей подпоследовательности. В следующей строке выведите k чисел — саму подпоследовательность.



"""

MINUS_INF = -10000
n_rows, n_columns = list(map(int, input().split()))
pole = []
max_pole = []
pole.append([MINUS_INF] * (n_columns + 1))
max_pole.append([MINUS_INF] * (n_columns + 1))
for i in range(n_rows):
    pole.append([MINUS_INF] + list(map(int, input().split())))
    max_pole.append(pole[-1].copy())
#max_pole = [[0] * (n_columns + 1)]* (n_rows + 1)
result_pole = [[""] * (n_columns + 1) for i in range(n_rows + 1)]
max_pole[1][1] = pole[1][1]
for i in range(1, n_rows + 1):
    for j in range(1, n_columns + 1):
        if (i == 1) & (j == 1):
            continue
        if (pole[i][j] + max_pole[i - 1][j]) > (pole[i][j] + max_pole[i][j - 1]):
            max_pole[i][j] = pole[i][j] + max_pole[i - 1][j]
            result_pole[i][j] = "U"
        else:
            max_pole[i][j] = pole[i][j] + max_pole[i][j - 1]
            result_pole[i][j] = "L"
i = n_rows
j = n_columns
path = ""
sum = pole[n_rows][n_columns]
while (i != 1) | (j != 1):
    if result_pole[i][j] == "U":
        path += "D"
        i -= 1
        sum += pole[i][j]
    else:
        path += "R"
        j -= 1
        sum += pole[i][j]
print(sum)
print(path[::-1])
