#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>

#include "util.h"
#include "clothing.h"


using namespace std;

Clothing::Clothing(const string category, const string name, 
	double price, int qty, string brand, string size)
	: Product(category, name, price, qty), brand_(brand), size_(size)
	{
		keywords_ = parseStringToWords(name_);
		set<string> brand_name = parseStringToWords(brand_);
		for(set<string>::iterator it = brand_name.begin(); it != brand_name.end(); ++it){
			keywords_.insert(*it);
		}
	}

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords() const{
	return keywords_;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
	set<string>::iterator it;
	vector<string>::iterator it2;
	for(it = keywords_.begin(); it != keywords_.end(); ++it){
		for(it2 = searchTerms.begin(); it2 != searchTerms.end(); ++it2){
			if(*it2 == *it){
				return true;
			}
		}
	}

	return false;
}

std::string Clothing::displayString() const{
	stringstream qq;
	qq << qty_;
	string q = qq.str();

	stringstream pp;
	pp << price_;
	string p = pp.str();

	return (name_ + "\n" + "Brand: " + brand_ + " " + "Size: " + size_ + "\n" + p + " " + q + " left");



}
void Clothing::dump(std::ostream& os) const{
	os << category_ << endl << name_ << endl << price_ 
	<< endl << qty_<< endl << size_ << endl << brand_ << endl;

}