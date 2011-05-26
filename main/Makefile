all: utils parallel test_parallel

utils: src/Common_Utils.cpp src/BigUInt_Utils.cpp src/BigUInt_Parallel_Utils.cpp
	g++ -g -c -Iinc/ src/Common_Utils.cpp -o obj/Common_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigUInt_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Parallel_Utils.cpp -o obj/BigUInt_Parallel_Utils.o

serial: src/BigUInt_Serial_Impl.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -g -c -Iinc/ src/BigUInt.cpp -o obj/BigUInt.o

parallel: src/BigUInt_Parallel_Impl.cpp 
	 g++ -g -c -Iinc/ src/BigUInt_Parallel_Impl.cpp -o obj/BigUInt_Parallel.o

test: utils serial test/p_add.cpp
	#g++ -c -Iinc/ test/s_add.cpp -o obj/s_add.o
	g++ -g -Iinc/ test/main.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt.o  -o obj/main

test_parallel: utils test/p_add.cpp
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt.o -o obj/p_add

clean:
	rm -r obj/*.o

