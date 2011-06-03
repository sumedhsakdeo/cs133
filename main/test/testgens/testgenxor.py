#!/usr/bin/python

import random
import math

cases = 200
print cases

doAnd = False 
doOr = False
doExor = True

for j in range(cases):
    a = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
    print a

    b = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 4294967295)
        b = b + digit * pow(4294967296,i)
    print b
    
    if doAnd:
        print a & b
    if doOr:
        print a | b
    if doExor:
        print a ^ b

