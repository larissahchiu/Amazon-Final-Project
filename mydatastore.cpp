#include "mydatastore.h"
#include "util.h"
#include "product.h"
#include <set>
#include <map>
#include <vector>
#include <string>

using namespace std;

MyDataStore::MyDataStore(){


}
 MyDataStore::~MyDataStore(){
 	for(vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
 		delete *it;
 	}
 	users_.clear();
 	for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
 		delete *it;
 	}
 	products_.clear();
     
     for(vector<Review*>::iterator it = reviews_.begin(); it!= reviews_.end(); ++it){
         delete *it;
     }
     reviews_.clear();

 }

	/**
     * Adds a product to the data store
     */
void MyDataStore::addProduct(Product* p){
	products_.push_back(p);
	set<string> keywords = p->keywords();
	for(set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it){
		productstoKeywords_[*it].insert(p);
	}
	std::set<std::string> s;
	userstoReviews_.insert(std::make_pair(p->getName(), s));
}

    /**
     * Adds a user to the data store
     */
void MyDataStore::addUser(User* u){
	users_.push_back(u);

}

void MyDataStore::addReview(Review* r){
	reviews_.push_back(r);
	for(unsigned int i = 0 ; i < products_.size(); i++){
		if(r->prodName == products_[i]->getName()){
			products_[i]->add_review(r);
		}
	}

	if(find_user(r->username) != NULL){
		find_user(r->username)->reviews_.push_back(r);
		userstoReviews_[r->prodName].insert(r->username);
	} 


}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	std::vector<Product*> v;

	if(terms.size() == 1){
		for(set<Product*>::iterator it = productstoKeywords_[terms[0]].begin(); 
			it != productstoKeywords_[terms[0]].end(); ++it){	
				v.push_back(*it);
		}
		return v;
	}
	
	set<Product*> compare = productstoKeywords_[terms[0]];

	if(type == 0){
		for(unsigned int i = 1; i < terms.size(); i++){
			compare = setIntersection(compare, productstoKeywords_[terms[i]]);
		}
	}
	
	else if(type == 1){
		for(unsigned int i = 1; i < terms.size(); i++){
			compare = setUnion(compare, productstoKeywords_[terms[i]]);
		}
	}
	
	for(set<Product*>::iterator it = compare.begin(); it != compare.end(); ++it){
		cout << (*it)->getName() << endl;
		v.push_back(*it);
	}

	return v;

}

    /**
     * Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;
	for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</products>" << endl << "<users>" << endl;
	for(vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</users>" << endl;

	ofile << "<reviews>" << endl;
	for(vector<Review*>::iterator it = reviews_.begin(); it !=reviews_.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</reviews>" << endl;

}


User* MyDataStore::find_user(std::string username){
	for(unsigned int i = 0; i < users_.size(); i++){
		if(users_[i]->getName() == username){
			return users_[i];
		}
	}

	return NULL;
}

Product* MyDataStore::find_product(std::string name){
	for(unsigned int i = 0; i < products_.size(); i++){
		if(products_[i]->getName() == name){
			return products_[i];
		}
	}
	return NULL;
}


void MyDataStore::add_to_cart(std::string username, Product* p){
	User* u = find_user(username);
	if(u == NULL){
		cout << "Invalid Request!" << endl;
		return;
	}

	u->addToCart(p);
}

void MyDataStore::view_cart(string username){

	User* u = find_user(username);
	if(u == NULL){
		cout << "Invalid Request!" << endl;
		return;
	}

	u->viewCart();
}

void MyDataStore::buy_cart(string username){
	User* u = find_user(username);
	if(u == NULL){
		cout << "Invalid Request!" << endl;
		return;
	}
	
	u->buyCart();

}

std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser){
	std::vector<std::pair<std::string, double> > suggestedProducts;
	//User* u = find_user(currentUser);

	for(unsigned int i = 0; i < products_.size(); i++){
		if(!products_[i]->usertoreview(currentUser)){
			std::pair<std::string, double> p(products_[i]->getName(), products_[i]->getAvg());
			suggestedProducts.push_back(p);
		}
	}

	//finds the suggestedProducts that are rated more than others
	for(unsigned int i = 0; i < suggestedProducts.size(); i++){
		//users of certain product
		std::set<std::string> p_users = userstoReviews_[suggestedProducts[i].first];
		double all = 0;
		double r = 0;
		//finds r(p) and w values over all users
		for(std::set<std::string>::iterator it = p_users.begin(); it != p_users.end(); ++it){
			r += (find_rating(suggestedProducts[i].first, *it)) * (1- find_user(*it)->dist);
			all +=  (1 - find_user(*it)->dist);
		}	

		//contains no reviews, p_for_a = 0;
		if(all == 0){
			suggestedProducts[i].second = 0;
		}

		//p_for_a = r(p) / w;
		else{
			suggestedProducts[i].second = r / all;
		}

	}

	SuggestionComp comp;
	mergeSort(suggestedProducts, comp);

	return suggestedProducts;

}

int MyDataStore::find_rating(std::string product, std::string user){
	for(unsigned int i = 0; i < find_product(product)->reviews_.size(); i++){
		if(find_product(product)->reviews_[i]->username == user) return find_product(product)->reviews_[i]->rating;
	}

	return 0;
}

