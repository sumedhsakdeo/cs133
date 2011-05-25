all: utils serial parallel

utils: src/BigUInt_Utils.cpp
	g++ -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigInt_Utils.o

serial: src/BigUInt_Serial_Impl.cpp src/BigUInt.cpp
	g++ -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -c -Iinc/ src/BigUInt.cpp -o obj/BigInt.o

parallel: src/OperationThread.cpp src/ThreadPool.cpp src/Parallelizer.cpp src/Thread.cpp
	g++ -c -Iinc/ src/Thread.cpp -o obj/Thread.o
	g++ -c -Iinc/ src/OperationThread.cpp -o obj/OperationThread.o
	g++ -c -Iinc/ src/ThreadPool.cpp -o obj/ThreadPool.o
	g++ -c -Iinc/ src/Parallelizer.cpp -o obj/Parallelizer.o


test:
	g++ -c -Iinc/ test/s_add.cpp -o obj/s_add.o
	cd obj
	./s_add
	cd ..    

clean:
	rm -r obj/*.o

