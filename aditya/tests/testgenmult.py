#!/usr/bin/python

import random
import math

#generates a large number

def genlargenum():
    a = 0
    for i in range(random.randint(500,1000)):
        a = 10 * a + random.randint(0,9)
    return a

#sum = 0
for j in range(100):
    a = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 2147483647)
        a = a + digit * pow(2147483648,i)
        #print i, digit
    #sum = sum + a
    print a

    b = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 2147483647)
        b = b + digit * pow(2147483648,i)
        #print i, digit
    #sum = sum + a
    print b
    print a * b

