all:
	g++ -Wall -O3 String_ops.cpp op_strings.cpp -o op_strings
	./path.sh
	g++ -Wall -O3 commutators.cpp -o commutators
clean:
	/bin/rm -rf op_strings
	/bin/rm -rf commutators.cpp 
	/bin/rm -rf commutators
tar:
	tar -cvf operators.tar *cpp *h Makefile test *sh
