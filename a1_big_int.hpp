#ifndef  A1_BIG_INT_HPP
#define A1_BIG_INT_HPP

#include "a1_doubly_linked_list.hpp"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class BigInt {
private:
	DoublyLinkedList* list;
public:
	BigInt(bool B[], int size);
	BigInt(string value);
	
	BigInt* add(BigInt* rhs);
	BigInt* sub(BigInt* rhs);
	BigInt* mul(BigInt* rhs);
	
	BigInt* bAnd(BigInt* rhs);
	BigInt* bOr(BigInt* rhs);
	BigInt* bXor(BigInt* rhs);
	
	
	
	//Helper Functions
	
	//Array Int to Array Bool
	void arrInt2arrBool(int* intArr, int intArrSize, int* binArr, int binArrSize);
	
	//All zeroes in array checker
	bool allZeroes(int* intArr, int intArrSize);
	
	//Array DivBy2
	void divBy2(int* intArr, int intArrSize);
	
	//Reversing Array
	void reverseArr( int array[], int length );
	
	//Accessor for list
	DoublyLinkedList* getList();
	
	//Common constructor code
	void init(bool B[], int size);
};
#endif 
