all:
	g++ -Wall -O3 String_ops.cpp op_strings.cpp -o op_strings
	./path.sh
	g++ -Wall -O3 commutators.cpp -o commutators
clean:
	/bin/rm -rf op_strings
