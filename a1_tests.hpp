#ifndef A1_TESTS_HPP
#define A1_TESTS_HPP

#include "a1_doubly_linked_list.hpp"
#include "a1_sequential_list.hpp"
#include "a1_big_int.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class SequentialListTest
{
public:
	// New empty list is valid
    bool test1()
    {
        unsigned int capacity = 5;
        SequentialList list(capacity);
        
        ASSERT_TRUE(list.size() == 0)
        ASSERT_TRUE(list.capacity() == capacity)
        ASSERT_TRUE(list.empty() == true)
        ASSERT_TRUE(list.full() == false)
        return true;
    }

	// insert_front() and insert_back() on zero-element list
    bool test2()
    {
        unsigned int capacity = 5;
        SequentialList list1(capacity);
        SequentialList list2(capacity);
        ASSERT_TRUE(list1.insert_front(100))
        ASSERT_TRUE(list2.insert_back(100))
    
        ASSERT_TRUE(list1.size() == list2.size() && list1.size() == 1)
        ASSERT_TRUE(list1.data_ != NULL)
        ASSERT_TRUE(list2.data_ != NULL)
        ASSERT_TRUE(list1.select(0) == list2.select(0) && list1.select(0) == 100)
        return true;
    }

	// select() and search() work properly
    bool test3()
    {
        unsigned int capacity = 5;
        SequentialList list(capacity);
        for (int i = 0; i < capacity; i++) {
            ASSERT_TRUE(list.insert_back(i*100))
        }
        
        unsigned int idx = 3;
        ASSERT_TRUE(list.search(list.select(idx)) == idx)
        ASSERT_TRUE(list.select(capacity + 1) == list.select(capacity))
        ASSERT_TRUE(list.search(1000) == list.size())
    
        for (int i = 0; i < capacity; i++) {
            ASSERT_TRUE(list.select(i) == i*100 && list.data_[i] == i*100)
        }
        return true;
    }
    
    // remove_front() and remove_back() on one-element list
    bool test4()
    {
	    unsigned int capacity = 5;
	    SequentialList list1(capacity);
	    SequentialList list2(capacity);
	    ASSERT_TRUE(list1.insert_front(100))
	    ASSERT_TRUE(list2.insert_front(100))
	    ASSERT_TRUE(list1.remove_front())
	    ASSERT_TRUE(list2.remove_back())
	
	    ASSERT_TRUE(list1.size_ == list2.size_ && list1.size_ == 0)
	    ASSERT_TRUE(list1.empty() == true && list2.empty() == true)
	    return true;
    }
    
    // Inserting too many elements should fail
    bool test5()
    {
    	unsigned int capacity = 5;
	    SequentialList list(capacity);
	    // Fill up the list.
	    for (int i = 0; i < capacity; i++) {
	        ASSERT_TRUE(list.insert_back(i))
	    }
	
	    // Try overfilling (they should all return false with no modifications).
	    int val_not_inserted = 100;
	    ASSERT_FALSE(list.insert_back(val_not_inserted))
	    ASSERT_FALSE(list.insert_front(val_not_inserted))
	    ASSERT_FALSE(list.insert(val_not_inserted, 3))
	
	    // Check size is correct.
	    ASSERT_TRUE(list.full() == true && list.empty() == false)
	    ASSERT_TRUE(list.size_ == list.capacity_ && list.capacity_ == capacity)
	
	    return true;
	}

    // insert_front() keeps moving elements forward
    bool test6()
    {
    	unsigned int capacity = 5;
	    SequentialList list(capacity);
	    for (int i = 0; i < capacity; i++) {
	        ASSERT_TRUE(list.insert_front(i))
	        ASSERT_TRUE(list.size_ == (i + 1))
	        for (int j = 0; j <= i; j++) {
	            SequentialList::DataType expected_value = i - j;
	            ASSERT_TRUE(list.data_[j] == expected_value)
	        }
	    }
	    return true;
	}
	
	// inserting at different positions in the list succeeds
    bool test7()
    {
    	unsigned int capacity = 10;
	    SequentialList list(capacity);
	    for (int i = 0; i < 4; i++) {
	        ASSERT_TRUE(list.insert_back(i))
	    }
	    ASSERT_TRUE(list.insert(4, 1))
	    ASSERT_TRUE(list.insert(5, 1))
	    ASSERT_TRUE(list.insert(6, 5))
	    ASSERT_TRUE(list.insert(7, 7))
	
	    // Check that the list has the right values.
	    int expected_values[] = {0, 5, 4, 1, 2, 6, 3, 7};
	    ASSERT_TRUE(list.size_ == 8)
	    for (int i = 0; i < list.size_; i++) {
	        ASSERT_TRUE(list.data_[i] == expected_values[i])
	    }
	
	    return true;
	}
	
	// try to remove too many elements, then add a few elements
    bool test8()
    {
    	unsigned int capacity = 5;
	    const int num_elems = 4;
	    SequentialList list(capacity);
	    for (int i = 0; i < num_elems; i++) {
	        ASSERT_TRUE(list.insert_back(i))
	    }
	    for (int i = 0; i < num_elems; i++) {
	        ASSERT_TRUE(list.remove_back())
	    }
	
	    // Try a bunch of invalid commands.
	    ASSERT_FALSE(list.remove_front())
	    ASSERT_FALSE(list.remove_front())
	    ASSERT_FALSE(list.remove(0))
	    ASSERT_TRUE(list.empty() && list.size_ == 0)
	
	    int expected_value = 1234;
	    ASSERT_TRUE(list.insert(expected_value, 0))
	    ASSERT_TRUE(list.data_[0] == expected_value)
	    return true;
	}
	
	// lots of inserts and deletes, some of them invalid
	bool test9() {
	   unsigned int capacity = 5;
	   SequentialList list(capacity);
	
	   ASSERT_FALSE(list.remove(0))
	   ASSERT_TRUE(list.insert_back(32))
	   ASSERT_TRUE(list.insert_front(44))
	   ASSERT_FALSE(list.insert(12,3))
	   ASSERT_TRUE(list.insert(12,2))
	   ASSERT_TRUE(list.remove_back())
	   ASSERT_FALSE(list.remove(5))
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.insert_back(88))
	   ASSERT_FALSE(list.insert(12345,6))
	   ASSERT_TRUE(list.remove(1))
	   ASSERT_TRUE(list.insert(99,0))  
	   
	   // Check that the list has the right values
	   ASSERT_TRUE(list.select(0) == 99 && list.data_[0] == 99)
	   ASSERT_TRUE(list.select(1) == 32 && list.data_[1] == 32)
	
	    return true;
	}
	
		// inserts into an unsorted list, then sort the list
	bool test10() {
	   unsigned int capacity = 5;
	   SequentialList list(capacity);
	   
	   ASSERT_TRUE(list.insert_back(25))
	   ASSERT_TRUE(list.insert_front(45))   
	   ASSERT_FALSE(list.insert_sorted_asc(25))
	   ASSERT_TRUE(list.insert(11,2))
	   ASSERT_TRUE(list.insert(15,2))
	   ASSERT_FALSE(list.insert_sorted_asc(35))
	   ASSERT_TRUE(list.insert(72,2))
	   
	   ASSERT_FALSE(list.is_sorted_asc())
	   list.sort_asc();
	   ASSERT_TRUE(list.is_sorted_asc())
		
	   SequentialList list2(capacity);      
	   ASSERT_TRUE(list2.insert_back(11))
	   ASSERT_TRUE(list2.insert_front(22))   
	   ASSERT_FALSE(list.insert_sorted_desc(25))
	   ASSERT_TRUE(list2.insert(55,2))
	   ASSERT_TRUE(list2.insert(31,2))
	   ASSERT_FALSE(list.insert_sorted_desc(35))   
	   ASSERT_TRUE(list2.insert(14,2))
	
	   ASSERT_FALSE(list2.is_sorted_desc())
	   list2.sort_desc();
	   ASSERT_TRUE(list2.is_sorted_desc())   
	   
	   return true;
	}
	
		// insert and remove into sorted list in ascending order
	bool test11() {
	   unsigned int capacity = 10;
	   SequentialList list(capacity);
	
	   ASSERT_TRUE(list.insert_sorted_asc(2))
	   ASSERT_TRUE(list.insert_sorted_asc(1))
	   ASSERT_TRUE(list.insert_sorted_asc(7))
	   ASSERT_TRUE(list.insert_sorted_asc(25))
	   ASSERT_TRUE(list.insert_sorted_asc(11))
	   ASSERT_TRUE(list.insert_sorted_asc(3))
	   ASSERT_TRUE(list.insert_sorted_asc(4))
	   ASSERT_TRUE(list.insert_sorted_asc(5))
	   ASSERT_TRUE(list.insert_sorted_asc(6))   
	   ASSERT_TRUE(list.insert_sorted_asc(1))
	   
	   ASSERT_TRUE(list.select(1) == 1 && list.data_[1] == 1);
	   ASSERT_TRUE(list.select(9) == 25 && list.data_[9] == 25);
	   ASSERT_TRUE(list.select(8) == 11 && list.data_[8] == 11);
	      
	   ASSERT_TRUE(list.remove_back())
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.insert_sorted_asc(0))
	   
	   ASSERT_TRUE(list.select(0) == 0 && list.data_[0] == 0);
	   ASSERT_TRUE(list.select(4) == 6 && list.data_[4] == 6);   
	   ASSERT_TRUE(list.select(3) == 5 && list.data_[3] == 5);
	   return true;
	}
	
	  //insert and remove into sorted list in descending order
	bool test12() {
	   unsigned int capacity = 10;
	   SequentialList list(capacity);	
		
	   ASSERT_TRUE(list.insert_sorted_desc(3))
	   ASSERT_TRUE(list.insert_sorted_desc(4))
	   ASSERT_TRUE(list.insert_sorted_desc(5))
	   ASSERT_TRUE(list.insert_sorted_desc(25))
	   ASSERT_TRUE(list.insert_sorted_desc(11))
	   ASSERT_TRUE(list.insert_sorted_desc(2))
	   ASSERT_TRUE(list.insert_sorted_desc(1))
	   ASSERT_TRUE(list.insert_sorted_desc(7))
	   ASSERT_TRUE(list.insert_sorted_desc(6))   
	   ASSERT_TRUE(list.insert_sorted_desc(1))
	   
	   ASSERT_TRUE(list.select(0) == 25 && list.data_[0] == 25);
	   ASSERT_TRUE(list.select(9) == 1 && list.data_[9] == 1);
	   ASSERT_TRUE(list.select(7) == 2 && list.data_[7] == 2);
	      
	   ASSERT_TRUE(list.remove_back())
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.insert_sorted_desc(0))
	   
	   ASSERT_TRUE(list.select(0) == 6 && list.data_[0] == 6);
	   ASSERT_TRUE(list.select(4) == 0 && list.data_[4] == 0);   
	   ASSERT_TRUE(list.select(1) == 5 && list.data_[1] == 5);
	   return true;
	}

};

class DoublyLinkedListTest
{
public:
	// New empty list is valid
    bool test1()
    {
		DoublyLinkedList list;
		ASSERT_TRUE(list.size() == 0)
		ASSERT_TRUE(list.empty() == true)
		ASSERT_TRUE(list.full() == false)
		ASSERT_TRUE(list.head_ == NULL)
		ASSERT_TRUE(list.tail_ == NULL)
	    return true;
    }

	// insert_front() and insert_back() on zero-element list
    bool test2()
    {
		DoublyLinkedList list1, list2;
		list1.insert_front(100);
		list2.insert_back(100);
	    
		ASSERT_TRUE(list1.size() == list2.size() && list1.size() == 1)
		ASSERT_TRUE(list1.head_ != NULL && list1.head_ == list1.tail_)
		ASSERT_TRUE(list2.head_ != NULL && list2.head_ == list2.tail_)
		ASSERT_TRUE(list1.head_->prev == NULL && list1.tail_->next == NULL)
		ASSERT_TRUE(list2.head_->prev == NULL && list2.tail_->next == NULL)
		ASSERT_TRUE(list1.select(0) == list2.select(0) && list1.select(0) == 100)
	    return true;
    }

	// select() and search() work properly
    bool test3()
    {
		DoublyLinkedList list;
		const int num_elems = 5;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(list.insert_back(i*100))
		}
	        
		unsigned int idx = 3;
		ASSERT_TRUE(list.search(list.select(idx)) == idx)
		ASSERT_TRUE(list.select(num_elems + 1) == 400)
		ASSERT_TRUE(list.search(1000) == list.size())
	    
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(list.select(i) == i*100)
		}
	    
		ASSERT_TRUE(list.head_->prev == NULL && list.tail_->next == NULL)
	        
	    return true;
    }
    
    // remove_front() and remove_back() on one-element list
    bool test4()
    {
    	DoublyLinkedList list1, list2;
	    ASSERT_TRUE(list1.insert_front(100))
	    ASSERT_TRUE(list2.insert_front(100))
	    ASSERT_TRUE(list1.remove_front())
	    ASSERT_TRUE(list2.remove_back())
	
		ASSERT_TRUE(list1.head_ == NULL && list1.tail_ == NULL)
	    ASSERT_TRUE(list2.head_ == NULL && list2.tail_ == NULL)
	    ASSERT_TRUE(list1.size_ == list2.size_ && list1.size_ == 0)
	    ASSERT_TRUE(list1.empty() == true && list2.empty() == true)
	    return true;
    }
    
    // replace() works properly
    bool test5()
    {
    	DoublyLinkedList list;
	    const int num_elems = 8;
	    for (int i = 0; i < num_elems; i++) {
	        ASSERT_TRUE(list.insert_back(i))
	    }
	
	    ASSERT_TRUE(list.replace(0, 8))
	    ASSERT_TRUE(list.replace(3, 9))
	    ASSERT_TRUE(list.replace(7, 10))
	
	    ASSERT_TRUE(list.head_->value == 8)
	    ASSERT_TRUE(list.tail_->value == 10)
	    ASSERT_TRUE((list.head_->next->next->next)->value == 9)
	
	    ASSERT_TRUE(list.head_->prev == NULL && list.tail_->next == NULL)
	    return true;
    }
    
    // insert_front() keeps moving elements forward
    bool test6()
    {
    	DoublyLinkedList list;
	    const int num_elems = 5;
	    for (int i = 0; i < num_elems; i++) {
	        ASSERT_TRUE(list.insert_front(i))
	        ASSERT_TRUE(list.size_ == (i + 1))
	        ASSERT_TRUE(list.head_->value == i)
	        
	        DoublyLinkedList::Node* n = list.head_;
	        for (int j = 0; j <= i; j++) {
	            DoublyLinkedList::DataType expected_value = i - j;
	            ASSERT_TRUE(n != NULL && n->value == expected_value)
	            n = n->next;
	        }
	    }
	    ASSERT_TRUE(list.head_->prev == NULL && list.tail_->next == NULL)
	    return true;
    }
    
    // inserting at different positions in the list
    bool test7()
    {
    	 DoublyLinkedList list;
	    for (int i = 0; i < 4; i++) {
	        ASSERT_TRUE(list.insert_back(i))
	    }
	    ASSERT_TRUE(list.insert(4, 1))
	    ASSERT_TRUE(list.insert(5, 1))
	    ASSERT_TRUE(list.insert(6, 5))
	    ASSERT_TRUE(list.insert(7, 7))
	
	    // Check that the list has the right values
	    int expected_values[] = {0, 5, 4, 1, 2, 6, 3, 7};
	    ASSERT_TRUE(list.size_ == 8)
	    DoublyLinkedList::Node* n = list.head_;
	    for (int i = 0; i < list.size_; i++) {
	        ASSERT_TRUE(n != NULL && n->value == expected_values[i])
	        n = n->next;
	    }
	
	    ASSERT_TRUE(list.head_->prev == NULL && list.tail_->next == NULL)
	    return true;
    }
    
    // try to remove too many elements, then add a few elements
    bool test8()
    {
    	DoublyLinkedList list;
	    const int num_elems = 4;
	    for (int i = 0; i < num_elems; i++) {
	        ASSERT_TRUE(list.insert_back(i))
	    }
	    for (int i = 0; i < num_elems; i++) {
	        ASSERT_TRUE(list.remove_back())
	    }
	
	    // Try a bunch of invalid commands.
	    ASSERT_FALSE(list.remove_front())
	    ASSERT_FALSE(list.remove_front())
	    ASSERT_FALSE(list.remove(0))
	    ASSERT_TRUE(list.empty() && list.size() == 0)
	
	    int expected_value = 1234;
	    ASSERT_TRUE(list.insert(expected_value, 0))
	    ASSERT_TRUE(list.head_->value == expected_value &&
	                list.tail_->value == expected_value)
	
	    ASSERT_TRUE(list.head_->prev == NULL && list.tail_->next == NULL)
	    ASSERT_TRUE(list.head_ == list.tail_)
	    return true;
    }
    
 	// lots of inserts and deletes, some of them invalid
	bool test9() {
		DoublyLinkedList list;
	
		ASSERT_FALSE(list.remove(0))
		ASSERT_TRUE(list.insert_back(32))
		ASSERT_TRUE(list.insert_front(44))
		ASSERT_FALSE(list.insert(12,3))
		ASSERT_TRUE(list.insert(12,2))
		ASSERT_TRUE(list.remove_back())
		ASSERT_FALSE(list.remove(5))
		ASSERT_TRUE(list.remove_front())
		ASSERT_TRUE(list.insert_back(88))
		ASSERT_FALSE(list.insert(12345,6))
		ASSERT_TRUE(list.remove(1))
		ASSERT_TRUE(list.insert(99,0))
		
		// Check that the list has the right values
		ASSERT_TRUE(list.select(0) == 99 && list.head_->value == 99)
		ASSERT_TRUE(list.select(1) == 32 && list.tail_->value == 32)
		
		ASSERT_TRUE(list.head_->next == list.tail_ && list.tail_->prev == list.head_)
		ASSERT_TRUE(list.head_->prev == NULL && list.tail_->next == NULL)
		return true;
	}    
	    	
		// inserts into an unsorted list, then sort the list
	bool test10() {
	   DoublyLinkedList list;
	
	   ASSERT_TRUE(list.insert_back(25))
	   ASSERT_TRUE(list.insert_front(45))   
	   ASSERT_FALSE(list.insert_sorted_asc(25))
	   ASSERT_TRUE(list.insert(11,2))
	   ASSERT_TRUE(list.insert(15,2))
	   ASSERT_FALSE(list.insert_sorted_asc(35))
	   ASSERT_TRUE(list.insert(72,2))
	   ASSERT_FALSE(list.is_sorted_asc())
	   list.sort_asc();
	   ASSERT_TRUE(list.is_sorted_asc())
	
		
	   DoublyLinkedList list2;      
	   ASSERT_TRUE(list2.insert_back(11))
	   ASSERT_TRUE(list2.insert_front(22))   
	   ASSERT_FALSE(list.insert_sorted_desc(25))
	   ASSERT_TRUE(list2.insert(55,2))
	   ASSERT_TRUE(list2.insert(31,2))
	   ASSERT_FALSE(list.insert_sorted_desc(35))   
	   ASSERT_TRUE(list2.insert(14,2))
	
	   ASSERT_FALSE(list2.is_sorted_desc())
	   list2.sort_desc();
	   ASSERT_TRUE(list2.is_sorted_desc()) 	
	
	   return true;
	}  
	
		// insert and remove into sorted list in ascending order
	bool test11() {
	   DoublyLinkedList list;
	
	   ASSERT_TRUE(list.insert_sorted_asc(2))
	   ASSERT_TRUE(list.insert_sorted_asc(1))
	   ASSERT_TRUE(list.insert_sorted_asc(7))
	   ASSERT_TRUE(list.insert_sorted_asc(25))
	   ASSERT_TRUE(list.insert_sorted_asc(11))
	   ASSERT_TRUE(list.insert_sorted_asc(3))
	   ASSERT_TRUE(list.insert_sorted_asc(4))
	   ASSERT_TRUE(list.insert_sorted_asc(5))
	   ASSERT_TRUE(list.insert_sorted_asc(6))   
	   ASSERT_TRUE(list.insert_sorted_asc(1))
	   
	   ASSERT_TRUE(list.select(0) == 1 && list.head_->value == 1);
	   ASSERT_TRUE(list.select(9) == 25 && list.tail_->value == 25);
	      
	   ASSERT_TRUE(list.remove_back())
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.insert_sorted_asc(0))
	   
	   ASSERT_TRUE(list.select(0) == 0 && list.head_->value == 0);
	   ASSERT_TRUE(list.select(4) == 6 && list.tail_->value == 6);   
	   return true;
	}
	
	  //insert and remove into sorted list in descending order
	bool test12() {
	   DoublyLinkedList list;
	
	   ASSERT_TRUE(list.insert_sorted_desc(3))
	   ASSERT_TRUE(list.insert_sorted_desc(4))
	   ASSERT_TRUE(list.insert_sorted_desc(5))
	   ASSERT_TRUE(list.insert_sorted_desc(25))
	   ASSERT_TRUE(list.insert_sorted_desc(11))
	   ASSERT_TRUE(list.insert_sorted_desc(2))
	   ASSERT_TRUE(list.insert_sorted_desc(1))
	   ASSERT_TRUE(list.insert_sorted_desc(7))
	   ASSERT_TRUE(list.insert_sorted_desc(6))   
	   ASSERT_TRUE(list.insert_sorted_desc(1))
	   
	   ASSERT_TRUE(list.select(0) == 25 && list.head_->value == 25);
	   ASSERT_TRUE(list.select(9) == 1 && list.tail_->value == 1);
	      
	   ASSERT_TRUE(list.remove_back())
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_back())   
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.remove_front())
	   ASSERT_TRUE(list.insert_sorted_desc(0))
	   
	   ASSERT_TRUE(list.select(0) == 6 && list.head_->value == 6);
	   ASSERT_TRUE(list.select(4) == 0 && list.tail_->value == 0);   
	   return true;
	}  
};

class BigIntTests
{
public:
	// Boolean Constructor: New empty BigInt is valid
    bool test1()
    {
    	bool A[1];
        BigInt* num = new BigInt(A,1);
        
        ASSERT_TRUE(num->getList()->size() == 1)
        ASSERT_TRUE(num->getList()->empty() == false)
        ASSERT_TRUE(num->getList()->full() == false)
		return true;
    }

	// Boolean Constructor: Smallest possible value is valid
    bool test2()
    {
    	bool B[1] = {true};
    	BigInt* num = new BigInt(B,1);
    	ASSERT_TRUE(num->getList()->size() == 1)
        ASSERT_TRUE(num->getList()->empty() == false)
        ASSERT_TRUE(num->getList()->full() == false)
        ASSERT_TRUE(num->getList()->select(0) == 1);
		return true;
    }

	// Boolean Constructor: Largest possible value is valid
    bool test3()
    {
    	bool B[1024];
    	for(int i = 0; i < 1024; i++){
    		B[i] = true;
		}
		BigInt* num = new BigInt(B,1024);
    	ASSERT_TRUE(num->getList()->size() == 32)
        ASSERT_TRUE(num->getList()->empty() == false)
        //Doubly Linked List can grow much larger than 32 nodes
        ASSERT_TRUE(num->getList()->full() == false)
        for(int i = 0; i < 31; i++){
        	ASSERT_TRUE(num->getList()->select(i) >= 4294967294U);
		}
		return true;
    }
    
    // String Constructor: New empty BigInt is valid
    bool test4()
    {
    	string input = "0";
    	BigInt* num = new BigInt(input);
    	ASSERT_TRUE(num->getList()->size() == 1)
        ASSERT_TRUE(num->getList()->empty() == false)
        ASSERT_TRUE(num->getList()->full() == false)
    	return true;
    }
    
    // String Constructor: Smallest possible value is valid
    bool test5()
    {
    	string input = "1";
    	BigInt* num = new BigInt(input);
    	ASSERT_TRUE(num->getList()->size() == 1)
        ASSERT_TRUE(num->getList()->empty() == false)
        ASSERT_TRUE(num->getList()->full() == false)
    	return true;
    }
    
    // String Constructor: Largest possible value is valid
    bool test6()
    {
    	string input = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215";
		BigInt* num = new BigInt(input);
    	ASSERT_TRUE(num->getList()->size() == 32)
        ASSERT_TRUE(num->getList()->empty() == false)
        //Doubly Linked List can grow much larger than 32 nodes
        ASSERT_TRUE(num->getList()->full() == false)
        for(int i = 1; i < 31; i++){
			//Accounting for machine rounding error
        	ASSERT_TRUE(num->getList()->select(i) >= 4294967294U);
		}
		return true;
    }
    
    // Addition of two single digit integers
    bool test7()
	{
		string input1 = "2", input2 = "5";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt(input1);
		temp = num1->add(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 7);
		return true;
	}
	
	// Addition of two double digit integers
	bool test8()
	{
		string input1 = "40", input2 = "20";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt(input1);
		temp = num1->add(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 60);
		return true;
	}
	
	// Addition of two 40 bit integers
	bool test9()
	{
		bool B[40],  C[40];
		for(int i = 0; i < 40; i++){
			B[i] = true;
			C[i] = true;
		}
		BigInt* num1 = new BigInt(B,40);
		BigInt* num2 = new BigInt(C,40);
		BigInt* temp = new BigInt(C,40);
		temp = num1->add(num2);
		ASSERT_TRUE(temp->getList()->size() == 2);
		ASSERT_TRUE(temp->getList()->select(0) == 510);
		//Accounting for machine rounding error
		ASSERT_TRUE(temp->getList()->select(1) >= 4294967294U);
		return true;
	}
	
	 // Subtraction of two single digit integers
    bool test10()
	{
		string input1 = "6", input2 = "3";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt(input1);
		temp = num1->sub(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 3);
		return true;
	}
	
	// Subtraction of two double digit integers
	bool test11()
	{
		string input1 = "40", input2 = "20";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt(input1);
		temp = num1->sub(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 20);
		return true;
	}
	
	// Subtraction of a forty bit and a thiry-eight bit integer
	bool test12()
	{
		bool B[40],  C[38];
		for(int i = 0; i < 40; i++){
			B[i] = true;
			if(i < 38)
			C[i] = true;
		}
		BigInt* num1 = new BigInt(B,40);
		BigInt* num2 = new BigInt(C,38);
		BigInt* temp = new BigInt("1");
		temp = num1->sub(num2);
		ASSERT_TRUE(temp->getList()->size() == 2);
		ASSERT_TRUE(temp->getList()->select(0) == 192);
		return true;
	}
	
	// Multiplicaiton of two single digit integers
    bool test13()
	{
		string input1 = "5", input2 = "3";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt(input1);
		temp = num1->mul(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 15);
		return true;
	}
	
	// Multiplication of two double digit integers
	bool test14()
	{
		string input1 = "40", input2 = "20";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt(input1);
		temp = num1->mul(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 800);
		return true;
	}
	
	// Multiplication of two ten bit integers
	bool test15()
	{
		bool B[10],  C[10];
		for(int i = 0; i < 20; i++){
			B[i] = true;
			C[i] = true;
		}
		BigInt* num1 = new BigInt(B,10);
		BigInt* num2 = new BigInt(C,10);
		BigInt* temp = new BigInt("1");
		temp = num1->mul(num2);
		ASSERT_TRUE(temp->getList()->size() == 1);
		//Accounting for machine rounding error
		ASSERT_TRUE(temp->getList()->select(0) >= 1046529);
		return true;
	}
	
	// And check between number and zero 
    bool test16()
	{
		string input1 = "10", input2 = "0";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bAnd(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 0)
		return true;
	}
	
	// And check between two numbers
	bool test17()
	{
		string input1 = "60", input2 = "13";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bAnd(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 12)
		return true;
	}
	
	// And check between the same numbers
	bool test18()
	{
		string input1 = "500", input2 = "500";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bAnd(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 500)
		return true;
	}
	
	// Or check between number and zero 
    bool test19()
	{
		string input1 = "1650", input2 = "0";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bOr(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 1650)
		return true;
	}
	
	// Or check between two numbers
	bool test20()
	{
		string input1 = "500", input2 = "30";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bOr(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 510)
		return true;
	}
	
	// Or check between the same numbers
	bool test21()
	{
		string input1 = "500", input2 = "500";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bOr(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 500)
		return true;
	}
	
	// Xor check between number and zero 
    bool test22()
	{
		string input1 = "2450", input2 = "0";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bXor(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 2450)
		return true;
	}
	
	// Xor check between two numbers
	bool test23()
	{
		string input1 = "330", input2 = "15";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bXor(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 325)
		return true;
	}
	
	// Xor check between the same numbers
	bool test24()
	{
		string input1 = "444", input2 = "444";
		BigInt* num1 = new BigInt(input1);
		BigInt* num2 = new BigInt(input2);
		BigInt* temp = new BigInt("1");
		temp = num1->bXor(num2);
		ASSERT_TRUE(temp->getList()->select(0) == 0)
		return true;
	}
};

#endif
