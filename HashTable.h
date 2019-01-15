
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Product.h"
using namespace std;


class HashTable {
private:
	int tableSize;
	int numCollisions;
	int elements;
	double distance;
	Product ** hashArray;
	Product *filler;
	int hash(string);
	int badHash(string key);

public:
	HashTable(int atableSize);
	~HashTable();
	void insertHash(Product*);
	void insertBadHash(Product*);
	bool deleteHash(string);
	int searchHash(string);
	void printHash() const;
	void displayInfo();
	int nextPrime(int);
	bool isPrime(int);
	void avgGaps();
	void printItem(int) const;
	int getArray() const;
	int getSize() const;

};



#endif // !HASHTABLE_H
