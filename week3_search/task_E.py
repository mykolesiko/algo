# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 22:45:28 2020

@author: Asus
"""

import math

def func(time, time_print, kol_prints, x_in, y_in):
    if (1 + (time - time_print) // x_in + (time - time_print) // y_in) >= kol_prints:
        return True
    else:
        return False
n, x, y = map(int, input().split())
time_min = min(x, y)
left = time_min
right = n * time_min
if right == left:
    itn = 1
else:
    itn = int(math.log((right - left), 2)) + 1
for i in range(itn):
    pivot = (left + right) // 2
    if func(pivot, time_min, n, x, y) == 0:
        left = pivot
    else:
        right = pivot
if func(left, time_min, n, x, y) == 1:
    print(left)
else:
    print(right)
    