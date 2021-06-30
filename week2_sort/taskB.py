# -*- coding: utf-8 -*-
"""
Created on Sun Sep 20 23:44:05 2020

@author: Asus
"""
N_MAX = 101
a = list(map(int, input().split()))
cnt = dict(zip(range(N_MAX), [0] * N_MAX))
for i in range(len(a)):
    cnt[a[i]] += 1
s = 0
for i in range(N_MAX):
    for j in range(cnt[i]):
        a[s] = i
        s += 1
print(' '.join(map(str, a)))
