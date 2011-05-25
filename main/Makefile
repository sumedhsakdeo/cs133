all: utils serial parallel

utils: src/BigUInt_Utils.cpp
	g++ -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigInt_Utils.o

serial: src/BigUInt_Serial_Impl.cpp src/BigUInt.cpp
	g++ -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -c -Iinc/ src/BigUInt.cpp -o obj/BigInt.o

parallel: src/OperationThread.cpp src/ThreadPool.cpp src/Parallelizer.cpp src/Thread.cpp
	g++ -c -lpthread -Iinc/ src/Thread.cpp -o obj/Thread.o
	g++ -c -lpthread -Iinc/ src/OperationThread.cpp -o obj/OperationThread.o
	g++ -c -lpthread -Iinc/ src/ThreadPool.cpp -o obj/ThreadPool.o
	g++ -c -lpthread -Iinc/ src/Parallelizer.cpp -o obj/Parallelizer.o


test: parallel test/*.cpp
	g++ -Iinc/ -lpthread test/p_add.cpp obj/Thread.o obj/OperationThread.o obj/ThreadPool.o obj/Parallelizer.o -o obj/p_add
	cd obj
	./p_add
	cd ..    

clean:
	rm -r obj/*.o

