#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) :
    p_for_a(0),
    name_(name),
    price_(price),
    qty_(qty),
    category_(category),
    avg_(0)
{

}

Product::~Product()
{

}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

double Product::getAvg() const {
    return avg_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& /*searchTerms*/) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

void Product::add_review(Review* r){
    reviews_.push_back(r);
    avg_ = (avg_ * (reviews_.size() - 1) + r->rating) / reviews_.size();
}

bool Product::usertoreview(std::string user){
    for(unsigned int i = 0; i < reviews_.size(); i++){
        if(reviews_[i]->username == user) return true;
    }
    return false;
}




