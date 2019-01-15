#include "Product.h"
#include <iostream>
#include <string>
using namespace std;

void Product::print() const {
	cout << "Name: " << name << endl;
	cout << "Primary Key(ASIN): " << asin << endl;
	cout << "Secondary Key(Rating): " << rating << endl;
	cout << "Distributor :" << distributor << endl;
	cout << "International Shipping: "  << interShip << endl << endl;
}