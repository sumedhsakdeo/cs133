all: utils parallel test_parallel

utils: src/Common_Utils.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/Common_Utils.cpp -o obj/Common_Utils.o
	g++ -g -c -Iinc/ src/BigUInt.cpp -o obj/BigUInt.o

serial: src/BigUInt_Utils.cpp src/BigUInt_Serial_Impl.cpp
	g++ -g -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigUInt_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	
parallel: src/BigUInt_Parallel_Utils.cpp src/BigUInt_Parallel_Impl.cpp
	g++ -g -c -Iinc/ src/BigUInt_Parallel_Utils.cpp -o obj/BigUInt_Parallel_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Parallel_Impl.cpp -o obj/BigUInt_Parallel.o

test_serial: utils serial test/main.cpp
	g++ -g -Iinc/ test/main.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt.o  -o obj/main

test_parallel: utils parallel test/p_add.cpp
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt.o -o obj/p_add

clean:
	rm -r obj/*.o

