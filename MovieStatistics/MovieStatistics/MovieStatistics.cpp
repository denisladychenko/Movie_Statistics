
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Value {
	int val;
	int count;
};

void loadArray(int*, const int&);
void sortArray(int*, const int&);
bool isInTheSet(vector<Value>, const int&);
double findMean(const int*, const int&);
vector<int>findMode(const int*, const int&);
double findMedian(const int*, const int&);

int main()
{
	int numStudents;          //number of students serveyed
	cout << "Enter how many students were serveyed? ";
	cin >> numStudents;
	//error checking
	while (numStudents < 1) {
		cout << "Enter how many students were serveyed? (at least 1) ";
		cin >> numStudents;
	}

	int* arrPtr = new int[numStudents];     //dynamically allocated array of students
	//load array
	loadArray(arrPtr, numStudents);
	//clear the screen
	system("cls");
	//sort the array in acsending order
	sortArray(arrPtr, numStudents);
	//output statistics
	cout << "Data: {";
	for (int i = 0; i < numStudents; i++) {
		if (i == numStudents - 1)
			cout << *(arrPtr + i);
		else
			cout << *(arrPtr + i) << ",";
	}
	cout << "}" << endl;
	vector<int> mode = findMode(arrPtr, numStudents);

	cout << "The mean is: " << findMean(arrPtr, numStudents) << endl;
	//if function returns -1 then there is no mode
	if (mode.at(0) == -1)
		cout << "There is no mode.";
	else {
		cout << "The mode is: ";
		for (int i = 0; i < mode.size(); i++) {
			cout << mode.at(i) << " ";
		}
	}
	cout << endl;
	cout << "The median is: " << findMedian(arrPtr, numStudents);
	cout << endl << endl;
	//free memory
	delete[] arrPtr;
	arrPtr = 0;
	system("pause");
    return 0;
}
/**
           loadArray
Gets input from the user and stores it into the array
@param arr the array
@param size the array size
*/
void loadArray(int* arr, const int& size) {
	for (int i = 0; i < size; i++) {
		cout << "Enter the number of movies student #" << i + 1 << " has seen:";
		cin >> *(arr + i);
	}
}
/**
                 sortArray
Sorts the array in acsending order
@param arr the array
@param size the array size
*/
void sortArray(int* arr, const int& size) {

	bool moved;
	int temp;
	do {
		moved = false;
		for (int i = 0; i < size - 1; i++) {
			if (*(arr + i) > *(arr + (i + 1))) {
				temp = *(arr + (i + 1));
				*(arr + (i + 1)) = *(arr + i);
				*(arr + i) = temp;
				moved = true;
			}
		}

	} while (moved);
}
/**
                   isInTheSet
Checks for existence of the value in the set
@param set the vector of value structures
@param val the value to search for
@returns true if value is in the set
*/
bool isInTheSet(vector<Value> set, const int& val) {
	int first = 0, last = set.size() - 1, middle = (first + last) / 2;
	bool found = false;
	while(!found && (first <= last)) {
		if (set.at(middle).val == val)
			return true;
		else if (set.at(middle).val < val) {
			first = middle + 1;
			middle = (first + last) / 2;
		}
		else if (set.at(middle).val > val) {
			last = middle - 1;
			middle = (first + last) / 2;
		}
		
	} 
	return false;
}
/**
                     findMean
Finds the mean of the set of values
@param arr the array
@param size the array size
@returns mean (as double)
*/
double findMean(const int* arr, const int& size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += *(arr + i);
	}
	return (sum / size);
}
/**
          findMode
Finds the mode of the set.
@param arr the array of values
@param size the size of the array
@return mode the vector of modes. If there is no mode
returns -1.
*/
vector<int>findMode(const int* arr, const int& size) {

	vector<Value> set;    //holds value:count pairs
	vector<int> modes;     //set of modes(if there few modes in the set
	bool noMode = false;   //flags if there is no mode in the set
	
		int max;            //max number of encounters
		//this loop finds all the different values in the set and creates
		//value:count pairs and stores them in the vector of structures
		for (int i = 0; i < size; i++) {
			if (!isInTheSet(set, *(arr + i))) {
				Value val;
				val.val = *(arr + i);
				val.count = 0;
				set.push_back(val);
			}
		}
		//this loop counts how many times each value has been encountered
		for (int i = 0; i < set.size(); i++) {
			for (int x = 0; x < size; x++) {
				if (set.at(i).val == *(arr + x)) {
					set.at(i).count++;
				}
			}

		}

		if (set.size() == 1) {             //special case for if there is only one
											//value in the set
			max = set.at(0).count;          //then mode is whatever value there is
		}
		else {
			noMode = true;
			max = set.at(0).count;
			//finds max number of encounters
			for (int i = 1; i < set.size(); i++) {
				if (set.at(i).count > max)
					max = set.at(i).count;
			}
			//determines if all the values in the set 
			//encountered the same number of times.If yes, there is no mode.
			for (int i = 0; i < set.size(); i++) {
				if (set.at(i).count != max) {
					noMode = false;
					break;
				}
		}
}

		if (noMode) {
			modes.push_back(-1);   //-1 indicates that there is no mode in the set
		}
		else {
			//creates the set of modes if there is more than one mode
			//if there is one mode it creates a set with one value
			for (int i = 0; i < set.size(); i++) {
				if (set.at(i).count == max) {
					modes.push_back(set.at(i).val);
				}
			}
		}


		return modes;
	}

/**
Determines the median of the set
@param arr the array pointer
@param numEl the number of elements in the array
@returns double the median of the set of values
*/
double findMedian(const int* arr, const int& size)
{
	//if there are even number of values in the set 
	//returns the avg of the middle two elements
	if (size % 2 == 0)
		return (*(arr + (size / 2)) + *(arr + ((size / 2) - 1))) / 2.0;
	//if there are odd number returns the element in the middle 
	else
		return *(arr + (size / 2));
}
