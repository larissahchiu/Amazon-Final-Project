#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>

#include "util.h"
#include "movie.h"


using namespace std;

Movie::Movie(const string category, const string name, 
	double price, int qty, string genre, string rating)
	: Product(category, name, price, qty), genre_(genre), rating_(rating)
	{
		keywords_ = parseStringToWords(name_);
		keywords_.insert(convToLower(genre_));
	}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
	return keywords_;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
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


std::string Movie::displayString() const{
	stringstream qq;
	qq << qty_;
	string q = qq.str();

	stringstream pp;
	pp << price_;
	string p = pp.str();

	return (name_ + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n" + p + " " + q + " left");





}
void Movie::dump(std::ostream& os) const{
	os << category_ << endl << name_ << endl << price_ << endl 
	<< qty_ << endl << genre_ << endl << rating_ << endl;

}