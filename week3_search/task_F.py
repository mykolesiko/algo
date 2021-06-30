# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 23:16:04 2020

@author: Asus
"""

import math

def time(x, a_gran, v_p, v_f):
    """ function returns time of road if the point of cross to forest has x coord"""
    time_loc = math.sqrt((1 - a_gran) ** 2 + x * x) / v_p +  \
               math.sqrt(a_gran ** 2 + (1 - x) ** 2) / v_f
    return time_loc    
v_p_in, v_f_in = map(int, input().split())
a_in = float(input())
EPS = 0.00001
left = 0.0
right = 1.0
itn = int(math.log((right - left)/EPS, 2)) + 1
for i in range(itn):
    pivot1 = (left + right) / 2 - EPS
    pivot2 = (left + right) / 2 + EPS
    if time(pivot1, a_in, v_p_in, v_f_in) < time(pivot2, a_in, v_p_in, v_f_in):
        right = pivot2
    else:
        left = pivot1
print(left)
