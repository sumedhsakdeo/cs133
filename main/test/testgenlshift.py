#!/usr/bin/python

import random
import math

cases = 200
print cases
#sum = 0
for j in range(cases):
    a = 0
    for i in range(random.randint(50,500)):
        digit = random.randint(0, 4294967295)
        a = a + digit * pow(4294967296,i)
        #print i, digit
    #sum = sum + a
    print a

    #b = random.randint(0, 4294967295)
    b = random.randint(1000, 4000)
    
    print b
    
    print a << b
