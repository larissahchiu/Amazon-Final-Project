#include "cart.h"

using namespace std;
Cart::Cart(){
	overallLayout = new QVBoxLayout();
	header = new QLabel("Select a Product: ");
	overallLayout->addWidget(header);

	list_ = new QListWidget();
	connect(list_, SIGNAL(currentRowChanged(int)), this, SLOT(setLocation(int)));
	overallLayout->addWidget(list_);

	error_all = new QLabel("Could not purchase full cart!");
	error_all->hide();
	overallLayout->addWidget(error_all);
	error_single = new QLabel("Could not purchase item!");
	error_single->hide();
	overallLayout->addWidget(error_single);

	buy_and_remove = new QHBoxLayout();
	overallLayout->addLayout(buy_and_remove);

	buy = new QPushButton("Buy Item");
	connect(buy, SIGNAL(clicked()), this, SLOT(buyItem()));
	buy_and_remove->addWidget(buy);
	remove = new QPushButton("Remove Item");
	connect(remove, SIGNAL(clicked()), this, SLOT(removeItem()));
	buy_and_remove->addWidget(remove);


	buyAll = new QPushButton("Buy All");
	connect(buyAll, SIGNAL(clicked()), this, SLOT(buycart()));
	overallLayout->addWidget(buyAll);

	close = new QPushButton("Close");
	connect(close, SIGNAL(clicked()), this, SLOT(quit()));
	overallLayout->addWidget(close);

	setLayout(overallLayout);
	
}


//with a new user, updates the cart
void Cart::setCart(User* u)
{
	u_ = u;
	setWindowTitle((QString::fromStdString(u->getName())) + "'s Cart");
	updateCart();

	
}

Cart::~Cart(){
	delete overallLayout;

	delete header;
	delete list_;

	delete error_all;
	delete error_single;

	delete buy_and_remove;
	delete buy;
	delete remove;
	delete buyAll;
	delete close;


}

//sets the item
void Cart::setLocation(int i){
	loc = i;
}

//updates cart when new item is added
void Cart::addItemtoCart(){
	updateCart();
}

//removes the item at index selected
void Cart::removeItem(){
	if(u_->cart_.size() == 0) return;
	error_single->hide();
	error_all->hide();
	u_->removefromCart(loc);
	updateCart();
}

//buys the whole cart 
void Cart::buycart(){
	if(u_->cart_.size() == 0) return;
	error_single->hide();
	error_all->hide();
	int c = u_->buyCart();
	if(c > 0) error_all->show();
	updateCart();
}

//buys individual item at the index given
void Cart::buyItem(){
	if(u_->cart_.size() == 0) return;
	error_single->hide();
	error_all->hide();
	int i = u_->buyItem(loc);
	if( i > 0 ) error_single->show(); 
	updateCart();
}
//closes the cart
void Cart::quit(){
	this->hide();
}
//update cart
void Cart::updateCart(){
	list_->clear();

	//fills in the cart with new values
	for(unsigned int i = 0; i < u_->cart_.size(); i++){
		std::stringstream ss;
		ss << u_->cart_[i]->getPrice();
		std::string s = ss.str();

		list_->addItem(QString::fromStdString(u_->cart_[i]->getName() + "\n " + s));
		
	}

	//sets 0 as index
	if(u_->cart_.size() > 0){
		list_->setCurrentRow(0); 
		loc = 0;

	}
	

	
}

