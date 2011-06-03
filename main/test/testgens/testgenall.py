#!/usr/bin/python

import random
import math

cases = 200
print cases

for j in range(cases):
    
    eqlflag = random.randint(0,19)
    digits = random.randint(50,500)

    a = 0
    for i in range(digits):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
    print a

    b = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 4294967295)
        b = b + digit * pow(4294967296,i)

    if eqlflag == 0:
        b = a

    print b

    c = random.randint(1000, 4000)
    print c

    print a + b
    if a < b:
        print '0'
    else:
        print a - b
    #print a - b
    print a * b
    print a & b
    print a | b
    print a ^ b
    
    d = ~a
    d = d + pow(2, 32*digits)
    print d

    print a << c
    print a >> c

    if a == b:
        print '1'
    else:
        print '0'
