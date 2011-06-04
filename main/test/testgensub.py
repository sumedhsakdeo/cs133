#!/usr/bin/python

import random
import math

cases = 20
print cases

for j in range(cases):
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
    
    if a < b:
        print '0'
    else:
        print a - b

