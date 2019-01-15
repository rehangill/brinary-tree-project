#include "BinarySearchTree.h"
#include "Product.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>


void intro();
char menu(char&);
void insertManager(BinarySearchTree<Product>*, BinarySearchTree<Product>*, HashTable&);
void managerMenu(BinarySearchTree<Product>*, BinarySearchTree<Product>*, HashTable&);
void deleteManager(BinarySearchTree<Product>*, BinarySearchTree<Product>*, HashTable&);
void searchManager(BinarySearchTree<Product>*, BinarySearchTree<Product>*, HashTable&);
void listManager(BinarySearchTree<Product>* , BinarySearchTree<Product>*, HashTable&);

void display(Product& item)
{
	cout << endl;
	cout << "--------------------------------" << endl;
	cout <<"Asinn:"<< item.getAsin() << endl;
	cout <<"Name:"<< item.getName() << endl;
	cout <<"Distributor:"<<item.getDistributor() << endl;
	cout <<"Rating:"<< item.getRating() << endl;
	cout <<"Intern:"<< item.getInterShip() << endl;
}

bool AsinCompare(Product &item1, Product &item2)
{
	if (item1.getAsin() > item2.getAsin())
	{
		return true;
	}
	else
		return false;
}

bool RatingCompare(Product &item1, Product &item2)
{
	if (item1.getRating() > item2.getRating())
	{
		return true;
	}
	else
		return false;
}

int lineInFile() {
	int count = 0;
	string temp;
	ifstream inputfile;
	inputfile.open("amazonInput.txt");
	if (!inputfile.good()) {
		cout << "Error opening file!\n";
		exit(-1);
	}
	while (!inputfile.eof()) {
		getline(inputfile, temp, '\n');
		count++;
	}
	inputfile.close();
	return count;
}
void indent(Product& indentNode, int level) {
	cout << level << ": " << indentNode.getAsin() << " "
		<< indentNode.getName() << " "
		<< indentNode.getDistributor() << " "
		<< indentNode.getRating() << " "
		<< indentNode.getInterShip() << endl;
}
int main()
{
	BinarySearchTree<Product>* TreePtr1 = new BinarySearchTree<Product>;
	BinarySearchTree<Product>* TreePtr2 = new BinarySearchTree<Product>;
	HashTable* table = new HashTable(lineInFile());
	Product temp;
	string buffer;
	float rating;
	ifstream inputfile;

	inputfile.open("amazonInput.txt");

	if (!inputfile)
	{
		cout << "Error open the file" << endl;
	}

	while (!inputfile.eof())
	{
		Product* hasptr = new Product();
		getline(inputfile, buffer, ';');
		temp.setAsin(buffer);

		hasptr->setAsin(buffer);

		getline(inputfile, buffer, ';');
		temp.setName(buffer);
		hasptr->setName(buffer);

		getline(inputfile, buffer, ';');
		temp.setDistributor(buffer);
		hasptr->setDistributor(buffer);

		getline(inputfile, buffer, ';');
		temp.setRating(buffer);
		hasptr->setRating(buffer);

		getline(inputfile, buffer, '\n');
		temp.setInterShip(buffer);
		hasptr->setInterShip(buffer);

		table->insertHash(hasptr);
		TreePtr1->insert(temp, AsinCompare);
		TreePtr2->insert(temp, RatingCompare);
	}

	intro();
//	table->printItem(table->searchHash("asdf"));
	managerMenu(TreePtr1, TreePtr2, *table);
	TreePtr1->printToFile(display);
	system("PAUSE");

}

void intro() {
	cout << "Welcome to the Amazon Product Database" << endl;
	cout << "Here you'll be able to view any product by its ASIN or by rating." << endl;
	cout << "You may also be able to view its distributor and whether it has internation shipping." << endl;
	cout << "-------------------------------------------------------------------------------------" << endl << endl;
}

char menu(char& key) {
	cout << "Please enter any of the following keys below to access their functions:\n\n"
		<< "I - Insert Manager\n"
		<< "D - Delete Manager\n"
		<< "L - List Manager\n"
		<< "S - Search Manager\n"
		<< "W - Write to File \n"
		<< "E - Exit Program\n";
		
	cin >> key;
	return key;
}

void managerMenu(BinarySearchTree<Product>* treePtr1, BinarySearchTree<Product>* treePtr2, HashTable& hashTable) {
	char key = ' ';
	while (key != 'E' || key != 'e') {
		menu(key);
		switch (key) {
		case 'i':
		case 'I': insertManager(treePtr1, treePtr2, hashTable); break;
		case 'd':
		case 'D': deleteManager(treePtr1, treePtr2, hashTable); break;
		case 'l':
		case 'L': listManager(treePtr1, treePtr2, hashTable); break;
		case 's':
		case 'S': searchManager(treePtr1, treePtr2, hashTable); break;
		case 'w':
		case 'W': treePtr1->printToFile(display); break;
		case 'e':
		case 'E': return;
		default: cout << "Not a valid input. Please try again!" << endl;
		}
	}
}


void insertManager(BinarySearchTree<Product>* treePtr1, BinarySearchTree<Product>* treePtr2, HashTable& hashTable){
	string buffer;
	Product temp, result;
	Product* hastemp = new Product();
	cin.ignore();
	cout << "Please enter the ASIN: ";
	getline(cin, buffer);
	temp.setAsin(buffer);
	hastemp->setAsin(buffer);
	if (hashTable.searchHash(buffer) != -1)
	{
		cout << "Product already exists" << endl;
		return;
	}
	cout << "Please enter the name of the product: ";
	getline(cin, buffer);
	temp.setName(buffer);
	hastemp->setName(buffer);
	cout << "Please enter the distributor: ";
	getline(cin, buffer);
	temp.setDistributor(buffer);
	hastemp->setDistributor(buffer);
	cout << "Please enter the rating: ";
	getline(cin, buffer);
	temp.setRating(buffer);
	hastemp->setRating(buffer);
	cout << "Does it have international shipping (True or False): ";
	getline(cin, buffer);
	temp.setInterShip(buffer);
	hastemp->setInterShip(buffer);

	treePtr1->insert(temp,AsinCompare);
	treePtr2->insert(temp,RatingCompare);
	hashTable.insertHash(hastemp);
}

void deleteManager(BinarySearchTree<Product>* treePtr1, BinarySearchTree<Product>* treePtr2, HashTable& hashTable){
	string buffer;
	Product temp, result;
	cout << "What Product would you like to delete?\n";
	cin >> buffer;
	temp.setAsin(buffer);
	bool found = false;

	if (treePtr1->getEntry(temp, result))
	{
		treePtr1->remove(temp);
		treePtr2->remove(temp);
		hashTable.deleteHash(buffer);
		if (found)
			cout << "The Product has been removed!\n";
	}
	else
		cout << "Couldn't delete Product\n";
}


void searchManager(BinarySearchTree<Product>* treePtr1, BinarySearchTree<Product>* treePtr2, HashTable& hashTable) {
	char key = ' ';
	Product target, result;
	string buffer;

	cout << "A - Search by ASIN.\n"
		<< "B - Search by Rating.\n"
		<< "C - Go back to the main menu.\n";
	cin >> key;
	switch (key) {
	case 'a':
	case 'A':
		cout << "Please enter ASIN: ";
		cin >> buffer;

		if (hashTable.searchHash(buffer)!= -1)
		{
			cout << "Found" << endl;
			hashTable.printItem(hashTable.searchHash(buffer));
		}
		else
		{
			cout << " Not found" << endl;
		}
		break; // primary key
	case 'b':
	case 'B':
		cin.ignore();
		cout << "Please enter the rating: ";
		getline(cin, buffer);
		target.setRating(buffer);
		if (treePtr2->getEntry(target, result))
		{
			display(result);
		}
		else
			cout << "NOT FOUND! " << endl;
		break; // secondary key
	case 'c':
	case 'C': break; // go back to main menu
	default: cout << "Not a valid input. Please try again!" << endl;
	}
}

void listManager(BinarySearchTree<Product>* treePtr1, BinarySearchTree<Product>* treePtr2, HashTable& hashTable) {
	char key = ' '; // initializer
	int level = 1; // initializer
	cout << "A - Print the list by unsorted order (in hash table sequence).\n"
		<< "B - Print the list by primary key order.\n"
		<< "C - Print the list by secondary key order.\n"
		<< "D - Print the list in (primary) indent order.\n"
		<< "E - Go back to the main menu.\n";
	cin >> key;
	switch (key) {
	case 'a':
	case 'A': hashTable.printHash(); hashTable.displayInfo(); break;
	case 'b':
	case 'B': treePtr1->inOrder(display); break; // primary key
	case 'c':
	case 'C': treePtr2->inOrder(display); break; // secondary key
	case 'd':
	case 'D': treePtr1->printTree(indent, level);
	case 'e':
	case 'E': break; // go back to main menu
	}
}