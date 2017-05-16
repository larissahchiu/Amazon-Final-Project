#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}

User::User(std::string name, double balance, int type, int password) :
   dist(1), pred(NULL), name_(name), balance_(balance), type_(type), password_(password)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

int User::getPassword() const{
	return password_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << " " << password_<<  endl;
}

void User::addToCart(Product* p){
	cart_.push_back(p);
}

int User::buyCart(){
	int i = 0;
	int size = cart_.size();
	int error = 0;
	while(i != size){
		if(balance_ - cart_[i]->getPrice() > 0 && cart_[i]->getQty() >= 1){
			cart_[i]->subtractQty(1);
			deductAmount(cart_[i]->getPrice());
			cart_.erase(cart_.begin() + i);
			size--;
		}
		else if(balance_ - cart_[i]->getPrice() < 0){
			cout << "Not enough money for "<< cart_[i]->getName() << endl;
			i++;
			error++;
		}
		else if(cart_[i]->getQty() <= 0){
			cout << cart_[i]->getName() << " is sold out!" << endl;
			i++;
			error++;
		}
		else{
			i++;
		}

	}

	return error;
}

void User::viewCart(){
	for(vector<Product*>::iterator it = cart_.begin(); it != cart_.end(); ++it){
		cout << (*it)->displayString() << endl;
	}
}

 void User::removefromCart(int i){
 	cart_.erase(cart_.begin() + i);
 }

 int User::buyItem(int i){
 	if(balance_ - cart_[i]->getPrice() > 0 && cart_[i]->getQty() >= 1){
			cart_[i]->subtractQty(1);
			deductAmount(cart_[i]->getPrice());
			cart_.erase(cart_.begin() + i);
		}
	else if(balance_ - cart_[i]->getPrice() < 0){
		cout << "Not enough money for "<< cart_[i]->getName() << endl;	
		return 1;
		}
	else if(cart_[i]->getQty() <= 0){
		cout << cart_[i]->getName() << " is sold out!" << endl;
		return 1;
		}

		return 0;
}
