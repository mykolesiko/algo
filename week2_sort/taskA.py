# -*- coding: utf-8 -*-
"""
Created on Tue Sep 22 20:01:52 2020

@author: Asus
"""
import random

def solve(b, k):
    """ функция обрабатывает один запрос """
    i = 0
    j = len(b) - 1
    result = b[i]
    while i < j:
        id_pivot = random.randint(i, j)
        pivot = b[id_pivot]
        m_1 = m_2 = i
        for s in range(i, j + 1, 1):
            if b[s] < pivot:
                b[s], b[m_1] = b[m_1], b[s]
                if m_1 != m_2:
                    b[s], b[m_2] = b[m_2], b[s]
                m_1 += 1
                m_2 += 1
            elif b[s] == pivot:
                b[s], b[m_2] = b[m_2], b[s]
                m_2 += 1
        if k < m_1:
            j = m_1 - 1
        elif (k >= m_1) & (k < m_2):
            result = pivot
            break
        else:
            i = m_2
        result = b[i]
    print(result)
       
n_a = int(input())
a = list(map(int, input().split()))
n_q = int(input())
for s in range(n_q):
    c = list(map(int, input().split()))
    i_in = c[0] - 1
    j_in = c[1] - 1
    k_in = c[2] - 1
    b_in = a[i_in : (j_in + 1)]
    solve(b_in, k_in)
    