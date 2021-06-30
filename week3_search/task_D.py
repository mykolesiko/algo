# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 20:42:14 2020

@author: Asus
"""
import math

def get_num_routes(len_route, n_routes_in, routes_in, k_houses_in):
    """ функция возврашает можно ли получить нужное число веревок длины len_route"""
    num_routes = 0
    for i in range(n_routes_in):
        num_routes += routes_in[i] // len_route
    return num_routes >= k_houses_in
ROUTE_MIN = 1
n_routes, k_houses = map(int, input().split())
routes = []
for i in range(n_routes):
    routes.append(int(input()))
#routes = list(map(int, input().split()))
left = len_routes_min = ROUTE_MIN #min(routes)
right = len_routes_max = max(routes)
if get_num_routes(left, n_routes, routes, k_houses) == 0:
    print(0)
else:
    if len_routes_max == len_routes_min:
        itn = 1
    else:
        itn = int(math.log(len_routes_max - len_routes_min, 2)) + 1
    for i in range(itn):
        pivot = (left + right) // 2
        if get_num_routes(pivot, n_routes, routes, k_houses) == 1:
            left = pivot
        else:
            right = pivot
    if  get_num_routes(right, n_routes, routes, k_houses) == 1:
        print(right)
    else:
        print(left)
       