# -*- coding: utf-8 -*-
"""
Created on Mon Sep 21 09:34:02 2020

@author: Asus

"""

from string import ascii_lowercase

params = list(map(int, input().split()))
n_str = int(params[0])
len_str = int(params[1])
n_fas = int(params[2])
strs = []
for i in range(n_str):
    strs.append(input())
result_in = range(n_str)
result_out = [0 for s in range(n_str)]
for i in range(len_str - 1, len_str - 1 - n_fas, -1):
    cnt = dict(zip(ascii_lowercase, [0] * len(ascii_lowercase)))
    for j in range(n_str):
        cnt[strs[j][i]] += 1
    p = dict(zip(ascii_lowercase, [0] * len(ascii_lowercase)))
    sum = 0
    for c in ascii_lowercase:
        p[c] = sum
        sum += cnt[c]
    for j in range(n_str):
        str_cur = strs[result_in[j]]
        c = str_cur[i]
        ind_c = p[c]
        result_out[ind_c] = result_in[j]
        p[c] += 1
    result_in = result_out[:]
for s in range(n_str):
    print(strs[result_out[s]])
    