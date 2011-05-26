all: utils serial test

utils: src/BigUInt_Utils.cpp
	g++ -g -c -Iinc/ src/BigUInt_Utils.cpp -o obj/BigInt_Utils.o

serial: src/BigUInt_Serial_Impl.cpp src/BigUInt.cpp
	g++ -g -c -Iinc/ src/BigUInt_Serial_Impl.cpp -o obj/BigUInt_Serial.o
	g++ -g -c -Iinc/ src/BigUInt.cpp -o obj/BigInt.o

test: test/p_add.cpp
	g++ -g -Iinc/ -lpthread test/p_add.cpp -o obj/p_add

clean:
	rm -r obj/*.o

