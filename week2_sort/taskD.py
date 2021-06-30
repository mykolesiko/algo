# -*- coding: utf-8 -*-
"""
Created on Wed Sep 23 15:11:44 2020

@author: Asus
"""



n1_n2_str = input()
str_in = input()
str_to_find = input()
 

#cnt_in = dict(zip(ascii_lowercase, [0] * len(ascii_lowercase)))
#cnt_find = dict(zip(ascii_lowercase, [0] * len(ascii_lowercase)))

FIRST_LETTER_CODE = 97  # ASCII-код буквы 'a'
LETTER_COUNT = 26  # Всего символов в диапазоне ['a' - 'z']

cnt_in = [0 for i in range(LETTER_COUNT)]  
  # кол-во каждого символа в строке t
cnt_find = [0 for i in range(LETTER_COUNT)]


for c in str_to_find:
    cnt_find[ord(c) - FIRST_LETTER_CODE] += 1
n_substr = 0
ptr = -1
for i in range(len(str_in)):
    
    ptr = max(ptr, i - 1)
    while (ptr < len(str_in) - 1 and cnt_in[ord(str_in[ptr + 1]) - FIRST_LETTER_CODE] < cnt_find[ord(str_in[ptr + 1])-FIRST_LETTER_CODE] ) :
        cnt_in[ord(str_in[ptr + 1]) - FIRST_LETTER_CODE] += 1
        ptr += 1
    n_substr += (ptr - i + 1)
    if ptr >= i:
        cnt_in[ord(str_in[i]) - FIRST_LETTER_CODE] -= 1
print(n_substr)
