#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QFileDialog>
#include <QDialog>
#include <QMessageBox>

#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

#include "mydatastore.h"
#include "cart.h"
#include "msort.h"
#include "writereview.h"
#include "util.h"
#include "heap.h"


class MainWindow : public QWidget{
	Q_OBJECT
public:
	MainWindow(MyDataStore* ds);
	~MainWindow();

private slots:
	void logIn();
	void createnewUser();

	void selectUser(int);
	void viewCart();
	void viewDatabase();
	void logOut();
	void Quit();

	void searchAND();
	void searchOR();

	void searchbyAlpha();
	void searchbyRating();

	void selectProduct(int i);
	void viewReviews();
	void addtoCart();
	void writeReview();

	void product_rec();
	void close_rec();


private:

	void showUsers();
	int hash(std::string p);

	//loginwindow
	QDialog* loginBox;
	QVBoxLayout* loginboxLayout;
	QLabel* username_label;
	QLineEdit* username_enter;
	QLabel* password_label;
	QLineEdit* password_enter;

	QPushButton* login_button;
	QPushButton* add_user_button;
	QPushButton* quit_user;

	QMessageBox* errormessage;

	//Overall Layout
	QHBoxLayout* overallLayout;


	//User selection
	QVBoxLayout* userLayout;
	/*QLabel* user_label;
	QListWidget* user_list;*/

	//Extra Functionalies
	QPushButton* view_cart;
	QPushButton* view_database;
	QPushButton* logout;
	QPushButton* quit;

	//Search
	QVBoxLayout* productLayout;

	QHBoxLayout* searchLayout;
	QLabel* search_label;
	QLineEdit* search_text;
	QPushButton* AND;
	QPushButton* OR;

	QHBoxLayout* search_by;
	QLabel* search_by_label;
	QRadioButton* alpha;
	QRadioButton* rating;

	QHBoxLayout* list_and_add;
    
    QVBoxLayout* products_box;
	QLabel* product_label;
	QListWidget* products;
	QHBoxLayout* product_button_layout;
    QPushButton* view_reviews;
    QPushButton* add_to_cart;
	QPushButton* write_review;

	QPushButton* product_rec_button;
	QDialog* product_rec_box;
	QVBoxLayout* product_rec_layout;
	QListWidget* product_rec_list;
	QPushButton* done;

    
    QVBoxLayout* review_layout;
    QLabel* review_label;
    QListWidget* reviews_list;
    
	
	//data members
	MyDataStore* ds_;
	int currUser;
	int currProduct;
	User* curr_user;
	Cart* cart_;
	WriteReview* wr_;

	std::vector<Product*> found_products;
	std::vector<Review*> review_list;

	int search; // 0 = alpha, 1 = rating;

};



#endif

