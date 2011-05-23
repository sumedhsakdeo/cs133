#!/usr/bin/python

import random
import math

#generates a large number

def genlargenum():
    a = 0
    for i in range(random.randint(500,1000)):
        a = 10 * a + random.randint(0,9)
    return a

sum = 0
for j in range(100):
    a = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
        #print i, digit
    sum = sum + a
    print a
print sum

