#!/usr/bin/python

import random
import math

#sum = 0
for j in range(100):
    a = 0
    digits = random.randint(50,500)
    for i in range(digits):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
        #print i, digit
    #sum = sum + a
    print a

    b = ~a
    b = b + pow(2, 32*digits)
    print b

