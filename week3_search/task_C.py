# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 19:55:37 2020

@author: Asus
"""
import math

def func(x):
    """ function = 0 to solve """
    return -(c_in  - x * x) * (c_in - x * x) + x


EPS = 0.0000001
c_in = float(input())
cmax_sqrt = math.sqrt(c_in)
left = 0.0
right = cmax_sqrt
itn = int(math.log((right - left)/EPS, 2))

for i in range(itn):
    pivot = (left + right) / 2
    if func(pivot) < 0:
        left = pivot
    else:
        right = pivot
print(left)
