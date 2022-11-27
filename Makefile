all:
	g++ -Wall -O3 String_ops.cpp op_strings.cpp -o op_strings
clean:
	/bin/rm -rf op_strings
