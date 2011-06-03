all: all_serial all_parallel test

all_parallel: utils parallel

all_serial: utils serial

utils: src/Common_Utils.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/Common_Utils.cpp -o obj/Common_Utils.o

serial: src/BigUInt_Utils.cpp src/BigUInt_Serial_Impl.cpp
	g++ -g -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigUInt_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -g -c -D SERIAL=1 -Iinc/ src/BigUInt.cpp -o obj/BigUInt_s.o
	
parallel: src/BigUInt_Parallel_Utils.cpp src/BigUInt_Parallel_Impl.cpp src/BigUInt.cpp
	g++ -g -c -D BLOCK_SIZE=120 -Iinc/ src/BigUInt_Parallel_Utils.cpp -o obj/BigUInt_Parallel_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Parallel_Impl.cpp -o obj/BigUInt_Parallel.o
	g++ -g -c -D PARALLEL=1 -Iinc/ src/BigUInt.cpp -o obj/BigUInt_p.o

test: test_serial test_parallel
	cp test/testall obj/

test_serial: utils serial test/main.cpp test/p_add.cpp
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o -o obj/s_add
	g++ -g -Iinc/ test/main.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/serial
	g++ -g -Iinc/ test/add.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/add_s
	g++ -g -Iinc/ test/sub.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/sub_s
	g++ -g -Iinc/ test/mult.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/mult_s
	g++ -g -Iinc/ test/div.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/div_s
	g++ -g -Iinc/ test/and.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/and_s
	g++ -g -Iinc/ test/or.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/or_s
	g++ -g -Iinc/ test/xor.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/xor_s
	g++ -g -Iinc/ test/not.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/not_s
	g++ -g -Iinc/ test/eq.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/eq_s

test_parallel: utils parallel test/p_add.cpp test/main.cpp
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/p_add
	g++ -g -Iinc/ -lpthread test/main.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/parallel
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

clean:
	rm -r obj/*.o
