	#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <string>

#include "util.h"
#include "book.h"


using namespace std;


Book::Book(const string category, const string name, double price, 
	int qty, string author, string isbn)
	: Product(category, name, price, qty), author_(author), isbn_(isbn)
	{
		set<string> author_set = parseStringToWords(author_);

		keywords_ = parseStringToWords(name_);

		for(set<string>::iterator it = author_set.begin(); it != author_set.end(); ++it){
			keywords_.insert(*it);
		}
		keywords_.insert(isbn_);

	}

Book::~Book(){

}

std::set<std::string> Book::keywords() const{
	return keywords_;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
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

std::string Book::displayString() const{
	stringstream qq;
	qq << qty_;
	string q = qq.str();

	stringstream pp;
	pp << price_;
	string p = pp.str();

	return (name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_ + "\n" + p + " " + q + " left");

}

void Book::dump(std::ostream& os) const{
	os << category_ << endl << name_ << endl << price_ << endl 
	<< qty_ << endl << isbn_ << endl << author_ << endl;

}