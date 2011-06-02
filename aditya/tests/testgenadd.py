#!/usr/bin/python

import random
import math

cases = 50
print cases

for j in range(cases):
    a = 0
    for i in range(50000):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
    print a

    b = 0
    for i in range(50000):
        digit = random.randint(0, 4294967295)
        b = b + digit * pow(4294967296,i)
    print b

    print a + b
