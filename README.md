# operators
Normal ordering and operations related to creation and annihilation operators
Developed by Dr. M. Rodriguez-Mayorga
email: marm3.14@gmail.com
At the Vrije Universiteit Amsterdam in Dec 2022


Installation
............

Simply run

$make

Description
...........

Operators package contains three codes developed to perform basic operations with creation and annihilation operators.
The first program is 

1) 

op_strings.cpp

This code reads from an input file a string of creation and annihilation operators, normal orders it, and prints the unique terms with
their corresponding factors (according to the number of times they appear). Examples of inputs and outputs are given in the test folder.
Notice that a strick format is required, where the first 5 columns must contain the factor (e.g. +1, -1, +200, etc.) used to multiply the
operators. Then, the operators used to form the string are made as follows: a) they must contain a label (e.g. b, a, p, etc), b) a type 
(c=creation, a=annihilation), and c) and index (e.g. p, q, r, s, i, a, etc.).
The label can be any character as well as the index (see the examples for more details). It is possible to provide as many lines of operators
as needed (this permits the evaluation of commutators).

2)

commutators_tmp.cpp 

Is a code design to read a commutator (also nested commutators) using square brackets and commas to delimitate the strings (i.e. [ ]). Examples 
are given in test_comm folder. The operators must be build using the same rules as in op_strings.cpp. This code will authomatically call op_strings
executable and provide the result of the commutator. The file ops_name.ops is produced with the result of the commutator including the Kronecker deltas.

3)

integrals_coefs.cpp

Is the last piece of code that uses a string of coefficients and integrals (see the test_int folder for more details), the information about the indices,
and the ops_name.ops file (produced by commutators) to transform the string of operators to reduced density matrix elements multiplied by the coefficients
and integrals. Ideally, in future versions, it will fully simplify the expressions using the Kronecker deltas information.
