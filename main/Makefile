all: objdir all_serial all_parallel

objdir:
	mkdir -p obj

all_parallel: utils parallel

all_serial: utils serial

utils: src/Common_Utils.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/Common_Utils.cpp -o obj/Common_Utils.o

serial: src/BigUInt_Utils.cpp src/BigUInt_Serial_Impl.cpp
	g++ -g -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigUInt_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -g -c -D SERIAL=1 -Iinc/ src/BigUInt.cpp -o obj/BigUInt_s.o
	
parallel: src/BigUInt_Parallel_Utils.cpp src/BigUInt_Parallel_Impl.cpp src/BigUInt.cpp
	g++ -g -c -D POOL_CNT=$(POOL_CNT) -D BLOCK_SIZE=$(BLOCK_SIZE) -Iinc/ src/BigUInt_Parallel_Utils.cpp -o obj/BigUInt_Parallel_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Parallel_Impl.cpp -o obj/BigUInt_Parallel.o
	g++ -g -c -D PARALLEL=1 -Iinc/ src/BigUInt.cpp -o obj/BigUInt_p.o

test: objdir test_serial test_parallel
	cp test/testall obj/
	chmod +x obj/testall
	test/gen-inputs.sh

run-test: test
	obj/testall

run-add: test
	@echo "ADD =>"
	@echo "Serial:"	
	obj/add_s obj/in_add
	@echo ""
	@echo "Parallel:"
	obj/add_p obj/in_add

run-sub: test
	@echo "SUB => "
	@echo "Serial:"
	obj/sub_s obj/in_sub
	@echo ""
	@echo "Parallel:"
	obj/sub_p obj/in_sub

run-mult: test
	@echo "MULT =>"
	@echo "Serial:"
	obj/mult_s obj/in_mul
	@echo ""
	@echo "Parallel:"
	obj/mult_p obj/in_mul

run-div: test
	@echo "DIV =>"
	@echo "Serial:"
	obj/div_s obj/in_div
	@echo ""
	@echo "Parallel:"
	obj/div_p obj/in_div

run-and: test
	@echo "AND =>"
	@echo "Serial:"
	obj/and_s obj/in_and
	@echo ""
	@echo "Parallel:"
	obj/and_p obj/in_and

run-or: test
	@echo "OR =>"
	@echo "Serial:"
	obj/or_s obj/in_or
	@echo ""
	@echo "Parallel:"
	obj/or_p obj/in_or

run-xor: test
	@echo "XOR =>"
	@echo "Serial:"
	obj/xor_s obj/in_xor
	@echo ""
	@echo "Parallel:"
	obj/xor_p obj/in_xor

run-not: test
	@echo "NOT =>"
	@echo "Serial:"
	obj/not_s obj/in_not
	@echo ""
	@echo "Parallel:"
	obj/not_p obj/in_not

run-eq: test
	@echo "EQ =>"
	@echo "Serial:"
	obj/eq_s obj/in_eq
	@echo ""
	@echo "Parallel:"
	obj/eq_p obj/in_eq

run-lshift: test
	@echo "LSHIFT =>"
	@echo "Serial:"
	obj/lshift_s obj/in_lshift
	@echo ""
	@echo "Parallel:"
	obj/lshift_p obj/in_lshift

run-rshift: test
	@echo "RSHIFT =>"
	@echo "Serial:"
	obj/rshift_s obj/in_rshift
	@echo ""
	@echo "Parallel:"
	obj/rshift_p obj/in_rshift

test_serial: all_serial
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o -o obj/s_add
	#g++ -g -Iinc/ test/main.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/serial
	g++ -g -Iinc/ test/add.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/add_s
	g++ -g -Iinc/ test/sub.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/sub_s
	g++ -g -Iinc/ test/mult.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/mult_s
	g++ -g -Iinc/ test/div.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/div_s
	g++ -g -Iinc/ test/and.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/and_s
	g++ -g -Iinc/ test/or.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/or_s
	g++ -g -Iinc/ test/xor.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/xor_s
	g++ -g -Iinc/ test/not.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/not_s
	g++ -g -Iinc/ test/eq.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/eq_s
	g++ -g -Iinc/ test/lt.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/lt_s
	g++ -g -Iinc/ test/gt.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/gt_s
	g++ -g -Iinc/ test/lshift.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/lshift_s
	g++ -g -Iinc/ test/rshift.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/rshift_s

test_parallel: all_parallel
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/p_add
	#g++ -g -Iinc/ -lpthread test/main.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/parallel
	g++ -g -Iinc/ -lpthread test/add.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/add_p
	g++ -g -Iinc/ -lpthread test/sub.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/sub_p
	g++ -g -Iinc/ -lpthread test/mult.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/mult_p
	g++ -g -Iinc/ -lpthread test/div.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/div_p
	g++ -g -Iinc/ -lpthread test/sub.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/sub_p
	g++ -g -Iinc/ -lpthread test/and.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/and_p
	g++ -g -Iinc/ -lpthread test/or.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/or_p
	g++ -g -Iinc/ -lpthread test/xor.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/xor_p
	g++ -g -Iinc/ -lpthread test/not.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/not_p
	g++ -g -Iinc/ -lpthread test/eq.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/eq_p
	g++ -g -Iinc/ -lpthread test/lt.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/lt_p
	g++ -g -Iinc/ -lpthread test/gt.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/gt_p
	g++ -g -Iinc/ -lpthread test/lshift.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/lshift_p
	g++ -g -Iinc/ -lpthread test/rshift.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/rshift_p

clean:
	rm -r obj
