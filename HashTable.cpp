#include "HashTable.h"
#include <iostream>
#include <iomanip>
using namespace std;

HashTable::HashTable(int numLines) {
	tableSize = nextPrime(numLines * 2);
	hashArray = new Product*[tableSize];
	for (int i = 0; i < tableSize; i++) {
		hashArray[i] = nullptr;
	}
	filler = new Product();
	filler->setAsin("Deleted");
	numCollisions = 0;
	elements = 0;
	distance = 0;
}

HashTable::~HashTable() {
	delete[] hashArray;
}

//-------------------------------------------------------
// Hash fuction adds the the ascii values of the amount of
// characters based on the table size to the 4th power
// Then modulo divides by the table size
//-------------------------------------------------------

int HashTable::hash(string key) {
	long temp = 0;
	for (int i = 0; i < key.length(); i++)
		temp += key[i] * key[i] * key[i] * key[i];
	return temp  % tableSize;
}

//-------------------------------------------------------
// Bad Hash Function adds all the ascii values of the key
// then modulo divides by 5
// Isn't evenly distributed and multiple collisions
//-------------------------------------------------------

int HashTable::badHash(string key) {
	long int sum = 0;
	for (int i = 0; i < key.length(); i++) {
		sum += key[i];
	}
	return sum % 11;
}

//-------------------------------------------------------
// Inserts pointer to object into an hash table
// Uses an alternating linear probe ex. +1, -2, +3, -4
//-------------------------------------------------------
void HashTable::insertHash(Product *newProduct) {
	Product *objPointer = newProduct;
	int count = 0;
	int arrOverflow = 0;
	bool inserted = false;
	int index = hash(objPointer->getAsin());
	while (!inserted) {
		arrOverflow = index + count;
		if (index != arrOverflow) {
			numCollisions++;
		}
		if (hashArray[arrOverflow] == nullptr) {
			hashArray[arrOverflow] = objPointer;
			elements++;
			inserted = true;
		}
		//Prevent array under/overflow
		if (count % 2 == 0) {
			count *= -1;
		}
		if (arrOverflow > tableSize) {
			arrOverflow = arrOverflow - tableSize - 1;
		}
		else if (arrOverflow < 0) {
			arrOverflow = tableSize + arrOverflow - 1;
		}
		count = abs(count) + 1;
	}
}

//-------------------------------------------------------
// Search functions uses same algorithm to find the index
// returns -1 if false, index when true
//-------------------------------------------------------
int HashTable::searchHash(string code) {
	int count = 0;
	bool found = false;
	int arrOverflow = hash(code);
	int index = arrOverflow;
	while (count < tableSize && !found && hashArray[arrOverflow] != nullptr) {
		//Prevent array under/overflow
		if (count % 2 == 0) {
			count *= -1;
		}
		arrOverflow = index + count;
		while(arrOverflow > tableSize)
		{
			arrOverflow = arrOverflow - tableSize-1;
		}
		while (arrOverflow < 0) {
			arrOverflow = tableSize + arrOverflow - 1;
		}
		if (hashArray[arrOverflow] != nullptr)
		{
			if (hashArray[arrOverflow]->getAsin() == code) {
				found = true;
				return arrOverflow;
			}
		}
		count++;
	}
	return -1;
}

//-------------------------------------------------------
// Deletes the object from the hash table
// replaces pointer to object to a pointer to a filler
//-------------------------------------------------------
bool HashTable::deleteHash(string product) {
	int index = searchHash(product);
	if (index != -1) {
		hashArray[index] = filler;
		elements--;
		cout<<" Product is succesfully deleted from the hash " << endl;
		return true;
	}
	else
	{
		cout << " Product wasnt found" << endl;
		return false;
	}
}

//-------------------------------------------------------
// Prints the full hash table
//-------------------------------------------------------
void HashTable::printHash() const {
	cout << "Hash Table:\n";
	for (int i = 0; i < tableSize; i++) {
		if (hashArray[i] != nullptr) {
			hashArray[i]->print();
		}
	}
}

//-------------------------------------------------------
// Finds the average distance between two elements
//-------------------------------------------------------
void HashTable::avgGaps() {
	double gap = 0;
	int j = 0;
	for (int i = 0; i < tableSize; i++) {
		j = 1;
		if (hashArray[i] != nullptr || (hashArray[i] != nullptr && hashArray[i]->getAsin() == "Deleted")) {
			while (hashArray[i + j] == nullptr) {
				gap++;
				j++;
			}
		}
	}
	distance = gap / elements;
}

//-------------------------------------------------------
// Prints a formatted display for information
//-------------------------------------------------------
void HashTable::displayInfo() {
	double loadFactor = (double(elements) / double(tableSize)) * 100;
	avgGaps();
	cout << "--------------------Hash Table Stats--------------------" << endl;
	cout << "Table size: " << tableSize << endl;
	cout << "Total number of elements: " << elements << endl;
	cout << "Total number of Collisions: " << numCollisions << endl;
	cout << "Total load Factor: " << fixed << setprecision(2) << loadFactor << "%" << endl;
	cout << "The average gap size (space between two elements): " << distance << endl;
	cout << "--------------------------------------------------------" << endl;
}

//-------------------------------------------------------
// Getter Function
//-------------------------------------------------------
int HashTable::getSize() const {
	return tableSize;
}

//-------------------------------------------------------
// Finds the next prime number
//-------------------------------------------------------
int HashTable::nextPrime(int n)
{
	int nextPrime = n;
	bool found = false;

	//loop continuously until isPrime returns true for a number above n
	while (!found)
	{
		nextPrime++;
		if (isPrime(nextPrime))
			found = true;
	}

	return nextPrime;
}

//given a number n, determine if it is prime
bool HashTable::isPrime(int n)
{
	//loop from 2 to n/2 to check for factors
	for (int i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)    //found a factor that isn't 1 or n, therefore not prime
			return false;
	}

	return true;
}
//-------------------------------------------------------
// Prints individual item
//-------------------------------------------------------
void HashTable::printItem(int index) const {
	if (index == -1)
	{
		cout << " Not found" << endl;
	}
	else
	hashArray[index]->print();
}