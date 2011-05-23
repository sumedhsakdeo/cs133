#!/usr/bin/python

import random
import math

#sum = 0
for j in range(100):
    a = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
        #print i, digit
    #sum = sum + a
    print a

    b = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 4294967295)
        b = b + digit * pow(4294967296,i)
        #print i, digit
    #sum = sum + a
    print b
    print a & b
    print a | b
    print a ^ b

