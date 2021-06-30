# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 11:57:24 2020

@author: Asus
"""

first = input()
array_A = list(map(int, input().split()))
array_B = list(map(int, input().split()))
n_A = len(array_A)
if n_A != 0:
    for el_b in array_B:
        if array_A[0] >= el_b:
            print(array_A[0])
        elif array_A[n_A - 1] <= el_b:
            print(array_A[n_A - 1])
        else:
            left = 0
            right = n_A  - 1
            while right >  left + 1:
                pivot = (right + left) // 2
                el_pivot = array_A[pivot]
                if el_pivot == el_b:
                    left = right = pivot
                elif el_pivot > el_b:
                    right = pivot
                else:
                    left = pivot
            if left == right:
                print(array_A[left])
            elif el_b - array_A[left] > array_A[left + 1] - el_b:
                print(array_A[left + 1])
            else:
                print(array_A[left])
                 