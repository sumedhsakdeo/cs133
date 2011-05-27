#!/usr/bin/python

import random
import math

cases = 200
print cases

for j in range(cases):
    a = 0
    digits = random.randint(50,500)
    for i in range(digits):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
    print a

    b = ~a
    b = b + pow(2, 32*digits)
    print b

