#include "a1_big_int.hpp"
#include <cstddef>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

BigInt::BigInt(bool B[], int size){
	init(B,size);
}

BigInt::BigInt(string value){
	//Case to handle 0 input from string constructor side	
	if(value == "0"){
		bool binArray[1] = {false};
		init(binArray,1);
	} else {
		int *decArray = new int[value.length()];
		for (int i=0; i<value.length(); i++){
			decArray[i]= (value.at(i)-'0');
		}
		
		int approxSize = value.length()/log10(2);
		int *tempBinArray = new int[approxSize];
		for (int i=0; i<approxSize; i++) { tempBinArray[i]=-1; }
		
		arrInt2arrBool(decArray, value.length(), tempBinArray, approxSize);
		reverseArr(tempBinArray, approxSize);
		
		int cnt=0;
		int wasteCounter=0;
		while (tempBinArray[cnt++]!=1 && cnt<approxSize){wasteCounter++;}
		
		int actualSize = approxSize-wasteCounter;
		bool* binArray = new bool[actualSize];
		int k=0;
		for (int j=wasteCounter; j<approxSize; j++){binArray[k++]=tempBinArray[j];}
		
		for (int i = 0; i < (actualSize / 2); i++) {
	        bool temp = binArray[i];               
	        binArray[i] = binArray[(actualSize - 1) - i];
	        binArray[(actualSize - 1) - i] = temp;
	    }
		
		init(binArray,actualSize);
	}	
	
}
//Utilized constructor function to allow for common usage of code
void BigInt::init (bool B[], int size){
	list = new DoublyLinkedList();
	unsigned int value;
	int counter = 0;
	int numNodes = size/32 + (size%32!=0?1:0);
	if(numNodes > 1){
		for(int i = 0; i < numNodes-1; i++){
			for(int j = 0; j < 32; j++){
				if(B[size-(1+j+i*32)] == true){
					value += pow(2,j);
				}
			}
			list->insert_back(value);
			value = 0;
		}
		for(int k = 0; k < size%32; k++){
			if(B[k] == true){
				value += pow(2,k);
			}
		}
		list->insert_back(value);
		value = 0;
	} else {
		value = 0;
		for(int k = 0; k < size; k++){
			if(B[k] == true){
				value += pow(2,k);
			}
		}
		list->insert_back(value);
		value = 0;
	}
}


BigInt* BigInt::add(BigInt* rhs){
	unsigned int num1, num2, sum;
	//Check the max number of nodes
	int maxNodes = (*this).list->size() > rhs->getList()->size() ? (*this).list->size() : rhs->getList()->size();
	string input = "1";
	//Declare output number
	BigInt* output = new BigInt(input);
	//Numbers to carry over
	unsigned int carry;
	//Iterate through all nodes
	for(int i = 0; i < maxNodes; i++){
		//Get value of of both BigInts at current node
		num1 = (*this).list->select(i);
		num2 = rhs->getList()->select(i);
		//Check if need to carry values from prev node
			if(carry != 0){
				sum += carry;
				carry = 0;
			}
			//calculate sum of present node
			sum = fmod(num1,pow(10,10)) + fmod(num2,pow(10,10));
			//Calculate whether sum will overflow from unsigned int
			carry = num1/pow(10,10) + num2/pow(10,10);
			sum += (carry%10)*pow(10,10);
			//If there is overflow, story it in carry
			if(carry/10 > 0){
				carry = carry%10;
			} else {
				carry = 0;
			}
		output->getList()->insert_front(sum);
	}
	output->getList()->remove_back();
	return output;
}

BigInt* BigInt::sub(BigInt* rhs){
	unsigned int num1, num2;
	int diff;
	bool extra = false;
	//Calculate max number of nodes
	int maxNodes = (*this).list->size() > rhs->getList()->size() ? (*this).list->size() : rhs->getList()->size();
	//Declare output number
	BigInt* output = new BigInt("1");
	//Iterate through each node
	for(int i = 0 ; i < maxNodes; i++){
		//Fetch the values of the BigInts at the present node
		num1 = (*this).getList()->select(i);
		num2 = rhs->getList()->select(i);
		//If both values are maxed out, we don't care about subtraction at this particular node
		if(num1 && num2 >= 4294967294U){
			diff = 4294967294U;
		} else {
			//Check if there was carry over from 
			if(extra){
				num1--;
				extra = false;
			}
			//Calculate difference
			diff = num1-num2;
			//Factor in negative cases
			if(diff < 0){
				diff += pow(10,10);
				extra = true;
			}
		}	
		output->getList()->insert_front(diff);
	}
	output->getList()->remove_back();
	return output;
}

BigInt* BigInt::mul(BigInt* rhs){
	//Calculate max number of Nodes
	int maxNodes = (*this).list->size() > rhs->getList()->size() ? (*this).list->size() : rhs->getList()->size();
	bool C[maxNodes];
	//Declare output
	BigInt* output = new BigInt(C,maxNodes);
	//Store product temporarily in a long long to prevent overflow
	long long product;
	unsigned int num1, num2, carry = 0;
	//Iterate through the nodes
	for(int i = 0; i < maxNodes; i++){
		//Fetch the value from the current node of this object
		num1 = (*this).list->select(i);
		//Alter the value based on carry from previous multiplicaitons
		if(carry != 0){
			num1 = fmod(num1,pow(10,10)) + fmod(carry,pow(10,10));
			carry = num1/pow(10,10) + carry/pow(10,10);
			num1 += (carry%10)*pow(10,10);
			if(carry/10 > 0){
				carry = carry%10;
			}
		}
		//Fetch the value from the inputted object
		num2 = rhs->getList()->select(i);
		//Calculate product and carry over
		product = num1 * num2;
		carry = product/ pow(10,10);
		output->getList()->insert_front(product);
		
	}
	output->getList()->remove_back();
	return output;
}

BigInt* BigInt::bAnd(BigInt* rhs){
	BigInt* output = new BigInt("1");
	int maxNodes = (*this).list->size() > rhs->getList()->size() ? (*this).list->size() : rhs->getList()->size();
	unsigned int num1, num2;
	//Iterate through nodes
	for(int i = 0; i < maxNodes; i++){
		//Fetch corresponding values to the nodes
		num1 = (*this).list->select(i);
		num2 = rhs->getList()->select(i);
		//Bitwise And comparison and store in output
		output->getList()->insert_front( num1 & num2 );
	}
	output->getList()->remove_back();
	return output;
}

BigInt* BigInt::bOr(BigInt* rhs){
	BigInt* output = new BigInt("1");
	int maxNodes = (*this).list->size() > rhs->getList()->size() ? (*this).list->size() : rhs->getList()->size();
	unsigned int num1, num2;
	//Iterate through nodes
	for(int i = 0; i < maxNodes; i++){
		//Fetch corresponding values to the nodes
		num1 = (*this).list->select(i);
		num2 = rhs->getList()->select(i);
		//Bitwise Or comparison and store in output
		output->getList()->insert_front( num1 | num2 );
	}
	output->getList()->remove_back();
	return output;
}

BigInt* BigInt::bXor(BigInt* rhs){
	BigInt* output = new BigInt("1");
	int maxNodes = (*this).list->size() > rhs->getList()->size() ? (*this).list->size() : rhs->getList()->size();
	unsigned int num1, num2;
	//Iterate through the nodes
	for(int i = 0; i < maxNodes; i++){
		//Fetch corresponding values to the nodes
		num1 = (*this).list->select(i);
		num2 = rhs->getList()->select(i);
		//Bitwise Xor comparison and store in output
		output->getList()->insert_front( num1 ^ num2 );
	}
	output->getList()->remove_back();
	return output;
}


//Helper Functions

//Array Int to Array Bool
void BigInt::arrInt2arrBool(int* intArr, int intArrSize, int* binArr, int binArrSize){
	int counter=0;
	while (!BigInt::allZeroes(intArr, intArrSize)){
		*(binArr+counter++)= *(intArr+intArrSize-1)%2;
		BigInt::divBy2(intArr, intArrSize);
	}	
}

//All zeroes in array checker
bool BigInt::allZeroes(int* intArr, int intArrSize){
	for (int i=0; i<intArrSize; i++){
		if (*(intArr+i)!=0) {return false;}
	}
	return true;
}

//Array DivBy2
void BigInt::divBy2(int* intArr, int intArrSize){
	for (int i=0; i<intArrSize; i++){
		*(i+intArr+1)+=((*(intArr+i)%2)*10); 
		*(intArr+i)=*(intArr+i)/2;
	}
}

//Reversing Array
void BigInt::reverseArr( int array[], int length )
{
    for (int i = 0; i < (length / 2); i++) {
        int temp = array[i];               
        array[i] = array[(length - 1) - i];
        array[(length - 1) - i] = temp;
    }
}

//Gain access to the list from the current object
DoublyLinkedList* BigInt::getList(){
	return (*this).list;
}

