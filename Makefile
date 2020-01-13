all: clean

partA: BinarySearchTree.cpp test.cpp


	g++ -std=c++11 -c BinarySearchTree.cpp
	ar -r BinarySearchTree.a BinarySearchTree.o
	g++ -std=c++11 -c test.cpp
	g++ -std=c++11 test.o BinarySearchTree.a -o test



partB: BinarySearchTree.cpp SpellCheck.cpp

	g++ -std=c++11 -c BinarySearchTree.cpp
	ar -r BinarySearchTree.a BinarySearchTree.o
	g++ -std=c++11 -c SpellCheck.cpp
	g++ -std=c++11 SpellCheck.o BinarySearchTree.a -o SpellCheck

clean:
	rm -f *.o 
	
	