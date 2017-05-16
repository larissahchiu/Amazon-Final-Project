#ifndef CART_H
#define CART_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

#include <vector>

#include "product.h"
#include "mydatastore.h"
#include "user.h"
#include "product.h"


class Cart : public QWidget{
	Q_OBJECT
public:
	Cart();
	void setCart(User* u);
	~Cart();

	void addItemtoCart();
	void updateCart();	

private slots:
	void setLocation(int i);
	void removeItem();
	void buyItem();
	void buycart();
	void quit();

private: 
	
	
	QVBoxLayout* overallLayout;

	QLabel* header;
	QListWidget* list_;

	QLabel* error_all;
	QLabel* error_single;

	QHBoxLayout* buy_and_remove;
	QPushButton* buy;
	QPushButton* remove;
	QPushButton* buyAll;
	QPushButton* close;

	int loc;
	User* u_;

};

#endif