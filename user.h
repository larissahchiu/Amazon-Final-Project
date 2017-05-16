#ifndef USER_H
#define USER_H
#include "product.h"
#include <iostream>
#include <string>
#include <vector>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    //User(std::string name, unsigned long long password);
    User(std::string name, double balance, int type, int password);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    int getPassword() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);

    void addToCart(Product* p);
    int buyCart();
    void viewCart();
    void removefromCart(int i);
    int buyItem(int i);

    std::vector<Product*> cart_;
    std::vector<Review*> reviews_;
    double dist;
    User* pred;


private:
    std::string name_;
    double balance_;
    int type_;
    int password_;


    
};
#endif
