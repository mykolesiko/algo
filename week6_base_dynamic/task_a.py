"""
https://codeforces.com/group/zJTwakJcKM/contest/299322/problem/A

A. Кузнечик собирает монеты
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Кузнечик прыгает по столбикам, расположенным на одной линии на равных расстояниях друг от друга. Столбики имеют порядковые номера от 1 до n. В начале Кузнечик сидит на столбике с номером 1 и хочет добраться до столбика с номером n. Он может прыгнуть вперед на расстояние от 1 до k столбиков, считая от текущего.

На каждом столбике Кузнечик может получить или потерять несколько золотых монет (для каждого столбика это число известно). Определите, как нужно прыгать Кузнечику, чтобы собрать наибольшее количество золотых монет. Учитывайте, что Кузнечик не может прыгать назад.

Входные данные
В первой строке вводятся два натуральных числа: n и k (3≤n≤10000, 1≤k≤10000), разделённые пробелом. Во второй строке записаны через пробел n−2 целых числа – количество монет, которое Кузнечик получает на каждом столбике, от 2-го до n−1-го. Если это число отрицательное, Кузнечик теряет монеты. Гарантируется, что все числа по модулю не превосходят 10000.

Выходные данные
В первой строке программа должна вывести наибольшее количество монет, которое может собрать Кузнечик. Во второй строке выводится число прыжков Кузнечика, а в третьей строке – номера всех столбиков, которые посетил Кузнечик (через пробел в порядке возрастания).

Если правильных ответов несколько, выведите любой из них.
"""

# -*- coding: utf-8 -*-
"""
Created on Thu Oct 22 12:42:50 2020

@author: Asus
"""

n_stolbs, max_len_step = list(map(int, input().split())) \
                         # количество столбиков, максимальный размер шага
moneys = list(map(int, input().split())) # массив изменения количества монет
moneys.append(0)
moneys.insert(0, 0)
steps = [] # массивы шагов с макс суммой монет для того \
                              # чтобы добраться к последним max_len_step элементам
max_money = [] # максимальные суммы для шагов steps
steps.append([0])
max_money.append(0)
for i in range(1, n_stolbs):
    temp_max = moneys[i] + max_money[-1]
    jmax = 0
    for j in range(0, max_len_step):
        temp = moneys[i]
        if (i - j - 1) < 0:
            break
        temp += max_money[-j - 1]
        if temp > temp_max:
            temp_max = temp
            jmax = j
    max_money.append(temp_max)
    steps.append(steps[-jmax - 1].copy())
    steps[-1].append(i)
    if len(max_money) > max_len_step:
        max_money.pop(0)
        steps.pop(0)
print(max_money[-1])
print(len(steps[-1]) - 1)
print(" ".join(list(map(lambda x: str(x + 1), steps[-1]))))
