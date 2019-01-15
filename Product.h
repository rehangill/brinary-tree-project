#pragma once
#ifndef PRODUCT_H	
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
	string name;
	string asin;
	string distributor;
	string rating;
	string interShip;
public:
	Product() { asin = ""; name = ""; distributor = ""; rating = ""; interShip = ""; }
	void setAsin(string asin) { this->asin = asin; }
	void setName(string name) { this->name = name; }
	void setDistributor(string distributor) { this->distributor = distributor; }
	void setRating(string rating) { this->rating = rating; }
	void setInterShip(string interShip) { this->interShip = interShip; }


	string getAsin() const { return asin; }
	string getName() const { return name; }
	string getDistributor() const { return distributor; }
	string getRating() const { return rating; }
	string getInterShip() const { return interShip; }
	void print() const;

};
#endif 
