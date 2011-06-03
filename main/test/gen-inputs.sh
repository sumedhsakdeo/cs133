#!/bin/bash
if [ ! -f obj/in_add ] ;
    then
    echo "python test/testgenadd.py > obj/in_add" 
    python test/testgenadd.py > obj/in_add
fi
if [ ! -f obj/in_sub ] ;
    then
    echo "python test/testgensub.py > obj/in_sub"
    python test/testgensub.py > obj/in_sub
fi
if [ ! -f obj/in_mul ] ;
    then
    echo "python test/testgenmult.py > obj/in_mul"
    python test/testgenmult.py > obj/in_mul
fi
if [ ! -f obj/in_div ] ;
    then
    echo "python test/testgendiv.py > obj/in_div"
    python test/testgendiv.py > obj/in_div
fi
if [ ! -f obj/in_and ] ;
    then
    echo "python test/testgenand.py > obj/in_and"
    python test/testgenand.py > obj/in_and
fi
if [ ! -f obj/in_or ] ;
    then
    echo "python test/testgenor.py > obj/in_or"
    python test/testgenor.py > obj/in_or
fi    
if [ ! -f obj/in_xor ] ;
    then
    echo "python test/testgenxor.py > obj/in_xor"
    python test/testgenxor.py > obj/in_xor
fi
if [ ! -f obj/in_not ] ;
    then
    echo "python test/testgennot.py > obj/in_not"
    python test/testgennot.py > obj/in_not
fi
if [ ! -f obj/in_eq ] ;
    then
    echo "python test/testgenequal.py > obj/in_eq"
    python test/testgenequal.py > obj/in_eq
fi
if [ ! -f obj/in_lshift ] ;
    then
    echo "python test/testgenlshift.py > obj/in_lshift"
    python test/testgenlshift.py > obj/in_lshift
fi
if [ ! -f obj/in_rshift ] ;
    then
    echo "python test/testgenrshift.py > obj/in_rshift"
    python test/testgenrshift.py > obj/in_rshift
fi
