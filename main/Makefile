all: all_serial all_parallel

all_parallel: utils parallel test_parallel

all_serial: utils serial test_serial

utils: src/Common_Utils.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/Common_Utils.cpp -o obj/Common_Utils.o

serial: src/BigUInt_Utils.cpp src/BigUInt_Serial_Impl.cpp
	g++ -g -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigUInt_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -g -c -D SERIAL=1 -Iinc/ src/BigUInt.cpp -o obj/BigUInt_s.o
	
parallel: src/BigUInt_Parallel_Utils.cpp src/BigUInt_Parallel_Impl.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/BigUInt_Parallel_Utils.cpp -o obj/BigUInt_Parallel_Utils.o
	g++ -g -c -Iinc/ src/BigUInt_Parallel_Impl.cpp -o obj/BigUInt_Parallel.o
	g++ -g -c -D PARALLEL=1 -Iinc/ src/BigUInt.cpp -o obj/BigUInt_p.o

test_serial: utils serial test/main.cpp test/p_add.cpp
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o -o obj/s_add
	g++ -g -Iinc/ test/main.cpp obj/Common_Utils.o obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt_s.o  -o obj/serial

test_parallel: utils parallel test/p_add.cpp test/main.cpp
	g++ -g -Iinc/ -lpthread test/p_add.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/p_add
	g++ -g -Iinc/ -lpthread test/main.cpp obj/Common_Utils.o obj/BigUInt_Parallel_Utils.o obj/BigUInt_Parallel.o obj/BigUInt_p.o -o obj/parallel

clean:
	rm -r obj/*.o
