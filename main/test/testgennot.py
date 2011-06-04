#!/usr/bin/python

import random
import math
import sys

digits = 1000
if len(sys.argv) == 2:
    digits = int(sys.argv[1])
low = 10 ** (digits - 1)
high = (10 ** digits) - 1

cases = 20
print cases

for j in range(cases):
    a = random.randint(low, high)
    print a

    b = ~a
    b = b + pow(2, 32*digits)
    print b

