all: utils serial test

utils: src/BigUInt_Utils.cpp
	g++ -g -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigUInt_Utils.o

serial: src/BigUInt_Serial_Impl.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -g -c -Iinc/ src/BigUInt.cpp -o obj/BigUInt.o

parallel:
	g++ -g -c -Iinc/ src/OperationThread.cpp -o obj/OperationThread.o
	g++ -g -c -Iinc/ src/ThreadPool.cpp -o obj/ThreadPool.o
	g++ -g -c -Iinc/ src/Parallelizer.cpp -o obj/Parallelizer.o

test: utils serial test/p_add.cpp
	#g++ -c -Iinc/ test/s_add.cpp -o obj/s_add.o
	g++ -g -Iinc/ test/main.cpp obj/BigUInt_Utils.o obj/BigUInt_Serial.o obj/BigUInt.o  -o obj/main
	g++ -g -Iinc/ -lpthread test/p_add.cpp -o obj/p_add

clean:
	rm -r obj/*.o

