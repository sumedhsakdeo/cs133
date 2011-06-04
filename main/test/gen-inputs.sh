#!/bin/bash
if [ ! -f obj/in_add ] ;
    then
    echo "python test/testgenadd.py $1 > obj/in_add" 
    python test/testgenadd.py $1 > obj/in_add
fi
if [ ! -f obj/in_sub ] ;
    then
    echo "python test/testgensub.py $1 > obj/in_sub"
    python test/testgensub.py $1 > obj/in_sub
fi
if [ ! -f obj/in_mul ] ;
    then
    echo "python test/testgenmult.py $1 > obj/in_mul"
    python test/testgenmult.py $1 > obj/in_mul
fi
if [ ! -f obj/in_div ] ;
    then
    echo "python test/testgendiv.py $1 > obj/in_div"
    python test/testgendiv.py $1 > obj/in_div
fi
if [ ! -f obj/in_and ] ;
    then
    echo "python test/testgenand.py $1 > obj/in_and"
    python test/testgenand.py $1 > obj/in_and
fi
if [ ! -f obj/in_or ] ;
    then
    echo "python test/testgenor.py $1 > obj/in_or"
    python test/testgenor.py $1 > obj/in_or
fi    
if [ ! -f obj/in_xor ] ;
    then
    echo "python test/testgenxor.py $1 > obj/in_xor"
    python test/testgenxor.py $1 > obj/in_xor
fi
if [ ! -f obj/in_not ] ;
    then
    echo "python test/testgennot.py $1 > obj/in_not"
    python test/testgennot.py $1 > obj/in_not
fi
if [ ! -f obj/in_eq ] ;
    then
    echo "python test/testgenequal.py $1 > obj/in_eq"
    python test/testgenequal.py $1 > obj/in_eq
fi
if [ ! -f obj/in_lshift ] ;
    then
    echo "python test/testgenlshift.py $1 > obj/in_lshift"
    python test/testgenlshift.py $1 > obj/in_lshift
fi
if [ ! -f obj/in_rshift ] ;
    then
    echo "python test/testgenrshift.py $1 > obj/in_rshift"
    python test/testgenrshift.py $1 > obj/in_rshift
fi
