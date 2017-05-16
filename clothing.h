#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product {
public:
	Clothing(const std::string category, const std::string name, double price, int qty, std::string brand, std::string size);
	virtual ~Clothing();
	virtual std::set<std::string> keywords() const;
	virtual bool isMatch(std::vector<std::string>& searchTerms) const;
	virtual std::string displayString() const;
	virtual void dump(std::ostream& os) const;

protected:
	std::string brand_;
	std::string size_;
	std::set<std::string> keywords_;

};

#endif