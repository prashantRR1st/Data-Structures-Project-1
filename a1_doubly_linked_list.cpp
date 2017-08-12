#include "a1_doubly_linked_list.hpp"
#include <cstddef>
#include <iostream>

using namespace std;

DoublyLinkedList::Node::Node(DataType data) //Init method for each node in doubly Linked List
{
	value = data;
	next = NULL;
	prev = NULL;
}

DoublyLinkedList::DoublyLinkedList() //Init method for single Doubly Linked List
{
	size_ = 0;
	head_ = NULL;
	tail_ = NULL;
}

DoublyLinkedList::~DoublyLinkedList() //Doubly Linked List Destructor
{
	if (size_==1){ //Single element => no iteration needed
		head_=NULL;
		tail_=NULL;
		delete head_;
		delete tail_;
	}else if (size_!=0){
		Node* temp1 = head_;
		Node* temp2;
		for (int i=0; i<size_; i++){ //List Iteration Loop
			temp2 = temp1->next;
			temp1=NULL;
			delete temp1;
			temp1=temp2; 
		}
	}
}

unsigned int DoublyLinkedList::size() const //Returns currently occupied number of nodes in list
{
	return size_;
}

unsigned int DoublyLinkedList::capacity() const //Returns list capacity
{
	return CAPACITY;
}

bool DoublyLinkedList::empty() const //Check for empty list
{
	return size_== 0;	
}

bool DoublyLinkedList::full() const //Check for full list
{
	return size_ == CAPACITY;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const //Accessing elements at particular index
{
	if(index > size_-1 || index < 0 || size_==1){ //Single element list OR invalid index exceptions
		return tail_->value;
	} else {
		Node* temp = head_;
		for (int i = 0; i <index; i++){
			temp = temp->next;
		}
		return temp->value;
	}
}

unsigned int DoublyLinkedList::search(DataType value) const //Returns index for given value
{
	Node* temp = head_;
	if (size_==0){ //empty list check
		return -1;
	}else if(temp->value == value){ //head element required element check
		return 0;
	}
	for(int i = 1; i < size_; i++){ //list loop
		temp = temp->next;
		if(temp-> value == value){
			return i;
		}
	}
	return size_;
}

void DoublyLinkedList::print() const //List display function
{
	Node* temp = head_;
	cout << temp->value << endl;
	for(int i = 1; i < size_; i++){
		temp = temp->next;
		cout << temp->value << ", "; 
	}
	cout<<endl;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const //returns pointer to node, given index value
{
	if(index > size_-1 || index < 0|| index == 0){ //invalid index and head exceptions
		return head_;
	} else if (index == size_-1){ //tail index condition
		return tail_;
	} else {
		Node* temp = head_;
		for(int i = 0; i < index;i++){
			temp = temp->next;
		}
		return temp;
	}
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
	
	if(index < 0 || index > size_ || size_ == CAPACITY){ //invalid index and full list conditions
		return false;
	} 
	Node* newNode = new Node(value);
	if (size_==0){ //empty list insert
			head_ = newNode;
			tail_ = newNode;
		}
	else if(index == 0){ //head position insert
		head_->prev = newNode;
		newNode->prev = NULL;
		newNode->next = head_;
		head_ = newNode;
	} else if(index == size_){ //tail position insert
		tail_->next = newNode;
		newNode->prev = tail_;
		newNode->next = NULL;
		tail_= newNode;	
	} else { //general position insert
		Node* temp = head_;
		for(int i = 1; i<index; i++){
			temp = temp->next;
		}
		newNode->prev = temp;
		newNode->next = temp->next;	
		temp->next->prev= newNode;
		temp->next = newNode;
		
	}
	size_++; //size of list incremented
	return true;
}

bool DoublyLinkedList::insert_front(DataType value) //calls general insert function for zero index
{
	return DoublyLinkedList::insert(value,0); 
}

bool DoublyLinkedList::insert_back(DataType value) //calls general insert for last position insert
{
	return DoublyLinkedList::insert(value, size_);
}

bool DoublyLinkedList::remove(unsigned int index) //removes particular indexed value from list
{
	if(index < 0 || index > size_-1 || size_==0){ //invalid index and empty list conditions
		return false;
	}
	Node* temp;
	if (size_==1){ //single element list remove
		delete head_;
		head_=NULL;
		tail_=NULL;
	} else if (index == 0){ //head remove
		temp = head_;
		head_ = head_->next;
		head_->prev = NULL;
		temp = NULL;
	} else if (index == size_-1){ // tail remove
		temp = tail_;
		tail_ = tail_->prev;
		tail_->next = NULL;
		temp = NULL;
	} else { //general remove
		for(int i = 0; i<index; i++){
			temp = temp->next;
		}
		(temp->prev)->next = (temp->next);
		(temp->next)->prev = (temp->prev);
		temp= NULL;
	}
	size_--; //list size decremented
	delete temp;
	return true;
} 

bool DoublyLinkedList::remove_front()//calls general remove function for head remove
{
	return DoublyLinkedList::remove(0);
}

bool DoublyLinkedList::remove_back()// calls general remove function for tail remove
{
	return DoublyLinkedList::remove(size_-1);
}

bool DoublyLinkedList::replace(unsigned int index, DataType value) //replacing value at given index with another value
{
	if(index < 0 || index > size_-1){ //invalid index condition
		return false;
	}
	if (index == 0){ //head replace
		head_->value = value;		
	} else if (index == size_-1){ //tailreplace
		tail_->value = value;
	} else { //general index replace
		Node* temp= head_;
		for(int i = 0; i<index; i++){
			temp = temp->next;
		}
		temp->value = value;
	}
	return true;
}

bool DoublyLinkedList::is_sorted_asc() const { //check to see if list is sorted in ascending order
	Node* temp = head_;
	if (size_==0){ //emty list considered sorted
		return true;
	} else{
		for (int i=0; i<size_-1; i++){
		if (temp->value > (temp->next)->value){
			return false; //breaks out of list index iteration if any one element isn't sorted
		}
		temp = temp->next;
	}
	}
	return true;
}

bool DoublyLinkedList::is_sorted_desc() const { //check to see if list is sorted in descending order
	Node* temp = head_;
	if (size_==0){ //emty list considered sorted
		return true;
	} else{
		for (int i=0; i<size_-1; i++){
		if (temp->value < (temp->next)->value){ //breaks out of list index iteration if any one element isn't sorted
			return false;
		}
		temp = temp->next;
		}
	}
	return true;
}

bool DoublyLinkedList::insert_sorted_asc(DataType val) { //inserting element in list whilst maintaining ascending order
	if (!DoublyLinkedList::is_sorted_asc()){ //check if list is sorted
		return false;
	} else if(size_==0){ //empty list check
		DoublyLinkedList::insert_front(val);
	}else if (val<= head_->value){ //less than (or =) head check
		DoublyLinkedList::insert_front(val);
	}else if (val>= tail_->value){ //greater than (or =) tail check
		DoublyLinkedList::insert_back(val);
	} else{ //general insert through iteration
		Node* temp = head_;
		for (int i=0; i<size_-1; i++){
			if (val>=(temp->value) && val<=((temp->next)->value)){
				DoublyLinkedList::insert(val, i+1);
				return true;
			}
			temp = temp->next;
		}
	}
	return true;
}

bool DoublyLinkedList::insert_sorted_desc(DataType val) { //inserting element in list whilst maintaining descending order
	if (!DoublyLinkedList::is_sorted_desc()){ //check if list is sorted
		return false;
	} else if(size_==0){ //empty list check
		DoublyLinkedList::insert_front(val);
	}else if (val>= head_->value){ //greater than (or =) head check
		DoublyLinkedList::insert_front(val);
	}else if (val<= tail_->value){ //less than (or =) tail check
		DoublyLinkedList::insert_back(val);
	} else{ //general insert through iteration
		Node* temp = head_;
		for (int i=0; i<size_-1; i++){
			if (val<=(temp->value) && val>=((temp->next)->value)){
				DoublyLinkedList::insert(val, i+1);
				return true;
			}
			temp = temp->next;
		}
	}
	return true;
}

void DoublyLinkedList::sort_asc() { //ascending order selection sort function
	if (DoublyLinkedList::empty() || DoublyLinkedList::is_sorted_asc()){ //check if sorted
		return;
	} else{ //Selection sort algorithm
		Node* temp1 = head_;
		Node* marker=temp1;
		for (int i=0; i<size_; i++){
			int min = temp1->value;
			Node* temp2 = temp1->next;
			for(int j=0; j<size_-1-i; j++){
				if (temp2->value<min){
					min = temp2->value;
					marker = temp2;
				}
				temp2 = temp2->next;				
			}
			int t = temp1->value;
			temp1->value = min;
			marker->value = t;
			temp1 = temp1->next;
		}
	}	
}
    
void DoublyLinkedList::sort_desc() { //descending order selection sort function
	if (DoublyLinkedList::empty() || DoublyLinkedList::is_sorted_desc()){ //check if sorted
		return;
	} else{ //Selection sort algorithm
		Node* temp1 = head_;
		Node* marker=temp1;
		for (int i=0; i<size_; i++){
			int max = temp1->value;
			Node* temp2 = temp1->next;
			for(int j=0; j<size_-1-i; j++){
				if (temp2->value>max){
					max = temp2->value;
					marker = temp2;
				}
				temp2 = temp2->next;				
			}
			int t = temp1->value;
			temp1->value = max;
			marker->value = t;
			temp1 = temp1->next;
		}
	}
}


