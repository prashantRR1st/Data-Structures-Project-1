#include <iostream>
#include <string>

#include "a1_tests.hpp"
#include "a1_big_int.hpp"

using namespace std;

string get_status_str(bool status)
{
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main()
{
    SequentialListTest seq_test;
    DoublyLinkedListTest linked_test;
    BigIntTests testCases;

	string seq_test_descriptions[12] = {
      "Test1: New empty list is valid",
      "Test2: insert_front() and insert_back() on zero-element list",
      "Test3: select() and search() work properly",      
	  "Test4: remove_front() and remove_back() on one-element list",
      "Test5: Inserting too many elements should fail",
      "Test6: insert_front() keeps moving elements forward",
      "Test7: inserting at different positions in the list",
      "Test8: try to remove too many elements, then add a few elements",
      "Test9: lots of inserts and deletes, some of them invalid",
      "Test10: inserts into an unsorted list, then sorts the list",      
      "Test11: insert and remove for sorted list in ascending order",
      "Test12: insert and remove for sorted list in descending order"  
	};
	
	bool seq_test_results[12];
    seq_test_results[0] = seq_test.test1();
    seq_test_results[1] = seq_test.test2();
    seq_test_results[2] = seq_test.test3();
    seq_test_results[3] = seq_test.test4();
    seq_test_results[4] = seq_test.test5();
    seq_test_results[5] = seq_test.test6();
    seq_test_results[6] = seq_test.test7();
    seq_test_results[7] = seq_test.test8();
    seq_test_results[8] = seq_test.test9();
    seq_test_results[9] = seq_test.test10();
    seq_test_results[10] = seq_test.test11();
    seq_test_results[11] = seq_test.test12();
    
	cout << "SEQUENTIAL LIST TESTING RESULTS \n";
	cout << "******************************* \n";
	for (int i = 0; i < 12; ++i) {
    	cout << seq_test_descriptions[i] << endl << get_status_str(seq_test_results[i]) << endl;
	}
	cout << endl;

	string linked_test_descriptions[12] = {
      "Test1: New empty list is valid",
      "Test2: insert_front() and insert_back() on zero-element list",
      "Test3: select() and search() work properly",
	  "Test4: remove_front() and remove_back() on one-element list",
      "Test5: replace() works properly",
      "Test6: insert_front() keeps moving elements forward",
      "Test7: inserting at different positions in the list",
      "Test8: try to remove too many elements, then add a few elements",
      "Test9: lots of inserts and deletes, some of them invalid",
      "Test10: inserts into an unsorted list, then sorts the list",      
      "Test11: insert and remove for sorted list in ascending order",
      "Test12: insert and remove for sorted list in descending order"   
	};
	
	bool linked_test_results[12];
    linked_test_results[0] = linked_test.test1();
    linked_test_results[1] = linked_test.test2();
    linked_test_results[2] = linked_test.test3();
    linked_test_results[3] = linked_test.test4();
    linked_test_results[4] = linked_test.test5();
    linked_test_results[5] = linked_test.test6();
    linked_test_results[6] = linked_test.test7();
    linked_test_results[7] = linked_test.test8();
    linked_test_results[8] = linked_test.test9();
    linked_test_results[9] = linked_test.test10();
    linked_test_results[10] = linked_test.test11();
    linked_test_results[11] = linked_test.test12();


	cout << "DOUBLY LINKED LIST TESTING RESULTS \n";
	cout << "********************************** \n";
	for (int i = 0; i < 12; ++i) {
    	cout << linked_test_descriptions[i] << endl << get_status_str(linked_test_results[i]) << endl;
	}
	cout << endl;
	
	string descriptions[24] = {
      "Test1: Boolean Constructor: New empty BigInt is valid",
      "Test2: Boolean Constructor: Smallest possible value is valid",
      "Test3: Boolean Constructor: Largest possible value is valid",
      "Test4: String Constructor: New empty BigInt is valid",
      "Test5: String Constructor: Smallest possible value is valid",
      "Test6: String Constructor: Largest possible value is valid",
      "Test 7: Addition of two single digit integers",
      "Test 8: Addition of two double digit integers",
      "Test 9: Addition of two fourty bit integers",
      "Test 10: Subtraction of two single digit integers",
      "Test 11: Subtraction of two double digit integers",
      "Test 12: Subtraction of a fourty bit and thirty-eight bit integer",
      "Test 13: Multiplication of two single digit integers",
      "Test 14: Multiplication of two double digit integers",
      "Test 15: Multiplication of two ten bit integers",
	  "Test 16: And check between number and zero",
	  "Test 17: And check between two numbers",
	  "Test 18: And check between same numbers",
	  "Test 19: Or check between number and zero",
	  "Test 20: Or check between two numbers",
	  "Test 21: Or check between same numbers",
	  "Test 22: Xor check between number and zero",
	  "Test 23: Xor check between two numbers",
	  "Test 24: Xor check between same numbers"
	};
	
	bool results[12];
    results[0] = testCases.test1();
    results[1] = testCases.test2();
    results[2] = testCases.test3();
    results[3] = testCases.test4();
    results[4] = testCases.test5();
    results[5] = testCases.test6();
    results[6] = testCases.test7();
    results[7] = testCases.test8();
    results[8] = testCases.test9();
    results[9] = testCases.test10();
    results[10] = testCases.test11();
    results[11] = testCases.test12();
    results[12] = testCases.test13();
    results[13] = testCases.test14();
    results[14] = testCases.test15();
    results[15] = testCases.test16();
    results[16] = testCases.test17();
    results[17] = testCases.test18();
    results[18] = testCases.test19();
    results[19] = testCases.test20();
    results[20] = testCases.test21();
    results[21] = testCases.test22();
    results[22] = testCases.test23();
    results[23] = testCases.test24();
    
	cout << "BIG INT TESTING RESULTS \n";
	cout << "******************************* \n";
	for (int i = 0; i < 24; ++i) {
    	cout << descriptions[i] << endl << get_status_str(results[i]) << endl;
	}
	cout << endl;
    system("pause");
}
