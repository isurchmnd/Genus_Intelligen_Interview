/*********************************************************************************************************************************************
 * Data Structure Homework - Genus Intelligen Interview 05/2019
 * Ryan Richmond
 * 
 * Create a data structure that will:
 * 
 * Use memory proportional to the number of contiguous ranges (using vector as storing, and shrink_to_fit to resize accordingly)
 * Support adding or removing ranges or individual integers in time proportional to the number of ranges.
 * Support querying for presence of ranges or individual integers in time that is proportional to the base2 logarithm of the number of ranges
 *    in the data structure. (Using a binary search on an ordered vector list to achieve this)
 * 
 * KNOWN ISSUE: Binary search is failing on multiple iterations as data inputs are being corrupted somehow. This is causing the adding, 
 *              deleting, and searching functionality to not work properly. 
 * 
 * *****************************************************************************************************************************************/
#include "stdafx.h"
#include "MainProgram.h"
#include "SearchFunctions.h"
#include "OptionFunctions.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int option_input = 99;
         
// Vector used as storage class for the range objects
vector <Node> range_storage;
vector<Node>::iterator it = range_storage.begin();

int main()
{
	cout << "Genus Intelligen Interview Homework - Ryan Richmond \n";
	
	baseFunction();

	return 0;
}

// Function: baseFunction()
// inputs: NONE
// outputs: NONE
// Requests user input through the console, checks that input is an integer, throws an error if its invalid and calls itself.
// Calls processInput if the input is indeed an integer.
void baseFunction()
{
	cout << "\nPlease slect from the following options: \n"
				"(0) add an integer\n"
				"(1) delete an integer\n"
				"(2) add a range\n"
				"(3) delete a range\n"
				"(4) search for an integer\n"
				"(5) search for a range\n"
				"(6) exit program\n\n";
	cin >> option_input;
	if (cin.fail())
	{
		cerr << "\nERROR: Input was not an integer. Please try again\n";
      cin.clear();
      cin.ignore(100, '\n');
      baseFunction();
	}
	else
	{
		processInput(option_input);
	}
}

// Function: processInput
// input: integer from the user through the console
// output: NONE
// Handles the user input by using a switch statment to call appropriate functions based on user selection. 
// Switch statement allows for easy user option expansion in the future. 
void processInput(int input)
{
	int integer_input = 0;
	int range_min = 0;
	int range_max = 0;

	switch (input)
	{
		// ADD AN INTEGER
		case 0:
			cout << "Please enter a valid integer: ";
			cin >> integer_input;
			//check if integer input is a valid integer
			if (cin.fail())
			{
				cerr << "\nERROR: Input was not an integer.\n";
            cin.clear();
            cin.ignore(100, '\n');
            baseFunction();
			}
			else
			{
				if (searchInteger(integer_input))
				{
					cout << integer_input << " already exists in the data structure, no action needed.\n";
				}
				else
				{
					addInteger(integer_input);
				}
			}
			baseFunction();
			break;
		// DELETE AN INTEGER	
		case 1:
			cout << "Please enter a valid integer: ";
			cin >> integer_input;
			//check if integer input is a valid integer
			if (cin.fail())
			{
				cerr << "\nERROR: Input was not an integer.";
            cin.clear();
            cin.ignore(100, '\n');
				baseFunction();
			}
			else
			{
				if (!searchInteger(integer_input))
				{
					cout << integer_input <<  " doesn't exist in the data structure, no action needed.\n";
				}
				else
				{
					deleteInteger(integer_input);
				}				
			}
			baseFunction();
			break;
		// ADD A RANGE
		case 2:
			cout << "Please enter a min and max integers for your range. Min first, followed by max: ";
			cin >> range_min >> range_max;
			//check if integer input is a valid integer
			if (cin.fail())
			{
				cerr << "\nERROR: One or more inputs were not valid integers.\n";
            cin.clear();
            cin.ignore(100, '\n');
				baseFunction();
			}
			else
			{
				if (searchRange(range_min, range_max))
				{
					cout << "Range " << range_min << " to " << range_max << " already exists in the data strucure, no action needed. \n";
				}
				else
				{
					addRange(range_min, range_max);
				}				
			}
			baseFunction();
			break;
		// DELETE A RANGE	
		case 3:
			cout << "Please enter a min and max integers for your range. Min first, followed by max: ";
			cin >> range_min >> range_max;
			//check if integer input is a valid integer
			if (cin.fail())
			{
				cerr << "\nERROR: One or more inputs were not valid integers.\n";
            cin.clear();
            cin.ignore(100, '\n');
				baseFunction();
			}
			else
			{
				if (!searchRange(range_min, range_max))
				{
					cout << "Range " << range_min << " to " << range_max << " does not exist in the data structure, no action needed.\n";
				}
				else
				{
					deleteRange(range_min, range_max);
				}
			}
			baseFunction();
			break;
		// SEARCH FOR AN INTEGER
		case 4:
			cout << "Please enter a valid integer: ";
			cin >> integer_input;
			//check if integer input is a valid integer
			if (cin.fail())
			{
				cerr << "\nERROR: Input was not an integer.\n";
            cin.clear();
            cin.ignore(100, '\n');
				baseFunction();
			}
			else
			{
				if (searchInteger(integer_input))
				{
					cout << integer_input << " exists in the data structure.\n";
				}
				else
				{
					cout << integer_input << " does not exist in the data structure.\n";
				}

			}
			baseFunction();
			break;
		// SEARCH FOR A RANGE
		case 5:
			cout << "Please enter a min and max integers for your range. Min first, followed by max: ";
			cin >> range_min >> range_max;
			//check if integer input is a valid integer
			if (cin.fail())
			{
				cerr << "\nERROR: One or more inputs were not valid integers.";
            cin.clear();
            cin.ignore(100, '\n');
				baseFunction();
			}
			else
			{
				if (searchRange(range_min, range_max))
				{
					cout << "The range " << range_min << " to " << range_max << " exists in the data structure. \n";
				}
				else
				{
					cout << "The range " << range_min << " to " << range_max << " does not exist in the data structure.\n";
				}
			}
			baseFunction();
			break;
		// EXIT
		case 6:
			exit(0);
			break;
      // NOT A USER OPTION, USED FOR DEBUGGING
      case 7:
         for (vector <Node>::const_iterator i = range_storage.begin(); i != range_storage.end(); ++i)
         {
            cout <<  i->range_min << ' ' << i->range_max << ' ' << "\n";
         }
         baseFunction();
         break;
      // ANY OTHER USER INPUT THAT IS OUTSIDE OF 0-6
		default://any other integer input that isn't 0-6
			cout << "Invalid selection, please try again \n";
			baseFunction();
			break;
	}        
}

// Function: binarySearch
// input: size of list to search, starting index, integer to search for
// output: index of list location that contains the searched integer
// Uses binary search algorithm to search the vector for the range that would contain the integer that was provided.
// Binary search has base-2-logorithmic performance for searching. 
int binarySearch(int start, int end, int input_integer)
{
   int middle = (end - start) / 2;
   vector <Node>::iterator index = range_storage.begin() + middle;
   
   if (end >= 2)
   {
      if (input_integer < index->range_min)
      {
         return binarySearch(start, middle, input_integer);
      }
      else if (input_integer > index->range_max)
      {
         return binarySearch(middle, end, input_integer);
      }
      else
      {
         return middle;
      }
   }
   else
   {
      if (input_integer < index->range_min)
      {
         return start;
      }
      else
      {
         return end;
      }
   }
}

// Function: makeNode
// input: min and max integers for creating a new range node
// output: node to be added to the list
Node makeNode(int min, int max)
{
	Node range;
	range.range_min = min;
	range.range_max = max;
	return range;
}


// Function: searchInteger
// input: integer to be searched for
// output: boolean value if the integer has been found or not
// Searches the vector list for the node that would contain the integer by comparing to the minimum value of the node
// once a node is found then verifies that integer falls between min and max of that node.
bool searchInteger(int x)
{
	int index = 0;
	int size = range_storage.size();

   if (size == 0)
	{
      //vector is empty
		return false;
	}
	else
	{
		index = binarySearch(0, size, x);

      if ((x >= range_storage[index].range_min) && (x <= range_storage[index].range_max))
		{
			
         return true;
		}
		else
		{
			return false;
		}
	}
}

// Function: searchRange
// input: min and max values of the range to be searched
// output: boolean value if the range as been found or not
// Searches the vector list for the node that would contain the range by comparing to the minimum value of the node
// once a node is found then verifies that range is either equal to the node found, or within the node that was found
bool searchRange(int min, int max)
{
	int index = 0;
	int size = range_storage.size();

	if (size == 0)
	{
		//vector is empty
		return false;
	}
	else
	{
      index = binarySearch(0, size, min);

	   if ((min >= range_storage[index].range_min) && (max <= range_storage[index].range_max))
	   {
         return true;
	   }
		else
		{
			return false;
		}
	}
}

// Function: addInteger
// input: integer to be added
// output: NONE
// Adds the supplied integer to the appropriate range, if no appropriate range exists, then one is created with
// the supplied integer as the min and the max of the range. 
void addInteger(int integer)
{
	int index = 0;

	//Check if range storage is empty
   if (range_storage.empty())
   {
      Node temp_range = makeNode(integer, integer);
      range_storage.push_back(temp_range);
   }
   else
   {
      index = binarySearch(0, range_storage.size(), integer);

	   if (range_storage[index].range_max == integer--) 
	   {
		   range_storage[index].range_max = range_storage[index].range_max++;
	   }
	   else if (range_storage[index + 1].range_min == integer++)
	   {
		   range_storage[index + 1].range_min = range_storage[index + 1].range_min--;
	   }
	   else
	   {
         Node new_range = makeNode(integer, integer);
         it = range_storage.begin() + index;
         range_storage.insert(it, new_range);
      }

      if (range_storage[index].range_max == (range_storage[index + 1].range_min - 1))
      {
         combineRanges(index, true);
      }
      else if (range_storage[index - 1].range_max == (range_storage[index].range_min -1))
      {
         combineRanges(index, false);
      }
      else
      {
         //DO NOTHING, NOTHING TO COMBINE
      }
   }  
   
}

// Function: deleteInteger
// input: integer to be added
// output: NONE
// Deletes the supplied integer from the appropriate range, if integer is neither the min or max of the range the range is
// split and a new range is created. 
void deleteInteger(int integer)
{
	int index = 0;

   if (range_storage.empty())
   {	
	   cout << "Data structure is empty, nothing to delete.\n";
      baseFunction();      
   }
   else
   {
      
      index = binarySearch(0, range_storage.size(), integer);

      if (range_storage[index].range_max == integer)
	   {
	   	range_storage[index].range_max = range_storage[index].range_max--;
	   }
	   else if (range_storage[index].range_min == integer)
	   {
	   	range_storage[index].range_min = range_storage[index].range_min++;
	   }
	   else
	   {
	   	Node new_range = makeNode(integer++, range_storage[index].range_max);
         range_storage[index].range_max = integer--;
         it = range_storage.begin() + index;
         range_storage.insert(it, new_range);
	   }
      range_storage.shrink_to_fit();
   }
}

// Function: combineRanges
// input: index of range that was found for adding an integer
// output: NONE
// When an integer is added, its possible that two previously disconnected ranges would become connected by the 
// new integer, this function combines those ranges and removes the one that is not longer needed. 
void combineRanges(int index, bool check)
{
	if (check)
   {
      range_storage[index].range_max = range_storage[index + 1].range_max;
      it = range_storage.begin() + (index + 1);
      range_storage.erase(it);
   }
   else
   {
      range_storage[index - 1].range_max = range_storage[index].range_max;
      it = range_storage.begin() + (index);
      range_storage.erase(it);
   }
  
	// size vector memory allocation to only use what is needed for the size of the vector. 
	range_storage.shrink_to_fit();
}

// Function: addRange
// input: min and max integer values for the range to be added. 
// output: NONE
// Verifies that range doesn't exists within another range.
// Extends existing ranges by either increaseing max, or decreasing min to accomodate integrating new range into existing.
// Absorbs existing range that might fall within new range
// if neither min or max are present in a previous range, then a whole new range is created. 
// Due to the way vectors allocate memory, calling shrink to fit at the end releases unused memory if allocated during range
// addition. 
void addRange(int min, int max)
{
	if (range_storage.empty())
	{
		Node new_node = makeNode(min, max);
      range_storage.push_back(new_node);
	}
   else
   {
      int index = 0;
      index = binarySearch(0, range_storage.size(), min);

      vector <Node>::iterator location = range_storage.begin() + index;

      if ((min < location->range_min) && ((max > location->range_min) && (max < location->range_max)))
      {
         location->range_min = min;
      }
      else if ((max > location->range_max) && ((min > location->range_min) && (min < location->range_max)))
      {
         location->range_max = max;
      }
      else
      {
         Node new_range = makeNode(min, max);
         range_storage.insert(location, new_range);
      }
      range_storage.shrink_to_fit();
   }
}

// Function: deleteRange
// input: min and max integer values for the range to be added. 
// output: NONE
// Decreases existing ranges by either increasing the min or decreasing the max to accomodate removing desired range
// If range to be deleted falls within an existing range, then range is split around deleted range accordingly 
// When range is deleted, shrink to fit is called to release memory that was made free up by deleting range. 
void deleteRange(int min, int max)
{
	int index = 0;

   if (range_storage.empty())
   {
      cout << "Data structure is empty, nothing to delete.";
      baseFunction(); 
   }
   else
   {
	   index = binarySearch(0, range_storage.size(), min);

	   if ((min > range_storage[index].range_min) && (max > range_storage[index].range_max))
	   {
	   	range_storage[index].range_max = min;
	   }
	   else if ((min < range_storage[index].range_min) && (max < range_storage[index].range_max))
	   {
	   	range_storage[index].range_min = max;
	   }
	   else
	   {
	   	Node new_range = makeNode(max, range_storage[index].range_max);
	   	range_storage[index].range_max = min;
	   	it = range_storage.begin() + index;
	   	range_storage.insert(it, new_range);
	   }
	   // size vector memory allocation to only use what is needed for the size of the vector. 
	   range_storage.shrink_to_fit();
   }
}

