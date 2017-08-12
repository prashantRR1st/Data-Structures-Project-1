#include <iostream>
using namespace std;

#include "a1_sequential_list.hpp"

//Constructor
SequentialList::SequentialList(unsigned int cap)
{
	//Initialize new list with inputted capacity
	data_ = new int[cap];
	capacity_ = cap;
	size_ = 0;
}

//Destructor
SequentialList::~SequentialList()
{
	delete[] data_;
	size_ = 0;
}

//Accessor for size of data
unsigned int SequentialList::size() const
{
	return size_;
}

//Accessor for capacity of list
unsigned int SequentialList::capacity() const
{
	return capacity_;
}

//Check if the list is empty
bool SequentialList::empty() const
{
	return (size_ == 0);
}

//Check if the list is full
bool SequentialList::full() const
{
	return (size_ == capacity_);
}

//Fetch a specific item from list
SequentialList::DataType SequentialList::select(unsigned int index) const
{
	//Check if the inputted index is invalid
	if(index > size_-1 || index<0)
		return *(data_ + size_-1);
		
	return *(data_ + index);
}

//Search list for a specific value
unsigned int SequentialList::search(DataType val) const
{
	for (int i = 0; i < size_; i++)
	{
		if(val == *(data_ +i))
			return i;
	}
	//If the value isn't found, return the size of the list
	return size_;
}

//Output the data in the list
void SequentialList::print() const
{
	for (int i = 0; i < size_; i++)
	{
		cout << *(data_ + i) << endl;
	}
}

//Check if the list is sorted in ascending order
bool SequentialList::is_sorted_asc() const 
{
	for(int i = 1; i < size_; i++)
	{
		if(*(data_ +i-1) > *(data_ + i))
		{
			//If the index before is larger, return false as it is not ascending
			return false;
		}
	}
	return true;	
}

//Check if the list is sorted in descending order
bool SequentialList::is_sorted_desc() const 
{
	for (int i = 1; i < size_; i++)
	{
		if(*(data_+i) > *(data_+i-1))
		{
			//If the index before is smaller, return false as it is not descending
			return false;
		}
	}
	return true;
}

//Insert a value into the list at the given index
bool SequentialList::insert(DataType val, unsigned int index)
{
	//Check if inputted index is invalid or list is full
	if(index < 0 || size_==capacity_ || index > size_)
	{
		return false;
	} 
	else 
	{
		//Move data upwards one index
		if(!SequentialList::empty())
		{
			for(int i = size_; i > index; i--)
			{
				*(data_+i) = *(data_ +i-1);
			}
		}
		//Insert data at inputted index
		*(data_ + index) = val;
		size_++;
		return true;
	}
}

//Insert value at the front of the list
bool SequentialList::insert_front(DataType val)
{
	return SequentialList::insert(val,0);
}

//Insert value at the back of the list
bool SequentialList::insert_back(DataType val)
{
	return SequentialList::insert(val,size_);
}

//Remove an item at the specified index
bool SequentialList::remove(unsigned int index)
{
	//Check if index is valid and that there are items in the list
	if(size_ == 0 || index < 0 || index >= size_)
	{
		return false;
	} 
	else 
	{
		//Move corresponding items in the list
		for(int i = index; i < size_-1; i++)
		{
			*(data_+i) = *(data_+i+1);
		}
		//Delete the item
		(data_ + size_-1) == NULL;
		size_--;
		return true;
	}
}

//Remove an item from the front of the list
bool SequentialList::remove_front()
{
	return SequentialList::remove(0);
}

//Remove an item from the back of the list
bool SequentialList::remove_back()
{
	return SequentialList::remove(size_-1);
}

//Replace an item at a specified index with another value
bool SequentialList::replace(unsigned int index, DataType val)
{
	//Check if index is invalid
	if(index < 0 || index >= size_)
	{
		return false;
	} 
	else 
	{
		//Replace value
		*(data_+index) = val;
		return true;
	}
}

//Insert value in its proper position in an ascending list
bool SequentialList::insert_sorted_asc(DataType val) 
{
	//Check if list is ascending or has space
	if(!SequentialList::is_sorted_asc() || size_==capacity_)
	{
		return false;
	} 
	else 
	{
		//Check if data can fit on either end of the list
		if(size_ == 0 || val <= *(data_))
		{
			SequentialList::insert_front(val);
		} 
		else if (val >= *(data_+size_-1))
		{
			SequentialList::insert_back(val);
		} 
		else 
		{
			//Iterate through the list and find the spot where the data should reside
			for(int i = 0; i < size_; i++)
			{
				if(val > *(data_+i) && val <= *(data_+i+1))
				{
					SequentialList::insert(val, i+1);
				}
			}
		}
		return true;
	}
}

//Insert value in its proper position in a descending list
bool SequentialList::insert_sorted_desc(DataType val) 
{
	//Check if list is descending or has space
	if(!SequentialList::is_sorted_desc() || size_==capacity_)
	{
		return false;
	} 
	else 
	{
		//Check if data can fit on either end of the list
		if(size_ == 0 || val >= *(data_))
		{
			SequentialList::insert_front(val);
		} 
		else if (val <= *(data_+size_-1))
		{
			SequentialList::insert_back(val);
		} 
		else 
		{
			//Iterate through the list and find the spot where the data should reside
			for (int i = 0; i < size_; i++)
			{
				if(val < *(data_+i) && val >= *(data_+i+1))
				{
					SequentialList::insert(val, i+1);
				}
			}
		}
		return true;
	}
}

//Sort the list in ascending order
//Selection Sort
void SequentialList::sort_asc() 
{
	int minIndex;
	DataType temp;
	//Loop through list
	for(int i = 0; i < size_-1 ; i++)
	{
		//set current index as lowest
		minIndex = i;
		//Loop through the rest of the list to try and find a smaller value
		for(int j = i+1; j < size_; j++)
		{
			//If there is one, swap the stored index
			if(*(data_+j) < *(data_+ minIndex))
			{
				minIndex = j;
			}
		}
		//If the smallest value isn't the current one, swap their positions in the list
		if(minIndex != i)
		{
			temp = *(data_+i);
			*(data_+i) = *(data_+minIndex);
			*(data_ + minIndex) = temp;
		}
	}
}
    
//Sort the list in descending order
//Selection Sort
void SequentialList::sort_desc() 
{
	int maxIndex;
	DataType temp;
	//Loop through the list
	for(int i = 0; i < size_-1 ; i++)
	{
		//Set current index as highest
		maxIndex = i;
		//Loop through the rest of the list to try and find a bigger value
		for(int j = i+1; j < size_; j++)
		{
			//If there is one, swap the stored index
			if(*(data_+j) > *(data_+ maxIndex))
			{
				maxIndex = j;
			}
		}
		//If the largest value isn't the current one, swap their positions in the list
		if(maxIndex != i)
		{
			temp = *(data_+i);
			*(data_+i) = *(data_+maxIndex);
			*(data_ + maxIndex) = temp;
		}
	}
}


