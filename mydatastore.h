#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include "datastore.h"
#include "msort.h"

class MyDataStore : public DataStore{
public:
	MyDataStore();
	virtual ~MyDataStore();
	
    virtual void addProduct(Product* p);

    
    virtual void addUser(User* u);
    
    virtual void addReview(Review* r);

    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    virtual void dump(std::ostream& ofile);

    void add_to_cart(std::string username, Product* p);
    void buy_cart(std::string username);
    void view_cart(std::string username);
    
    std::vector<User* > users_;
    std::vector<Product* > products_;

    User* find_user(std::string username);
    Product* find_product(std::string username);

    std::map<std::string, std::set<std::string> > userstoReviews_;
    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);
    int find_rating(std::string product, std::string user);
private:
    std::vector<Review* > reviews_;
	
	std::map< std::string, std::set<Product*> > productstoKeywords_; 
   // std::map<std::string, std::set<Review*> > reviewstoProducts_;

};


#endif
