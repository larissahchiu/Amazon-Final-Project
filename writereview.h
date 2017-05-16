#ifndef WRITEREVIEW_H
#define WRITEREVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QPushButton>

#include <string>
#include "user.h"
#include "product.h"
#include "mydatastore.h"
#include "review.h"

class WriteReview : public QWidget {
	Q_OBJECT
public:
	WriteReview();
	void setWrite(User* u, Product* p, MyDataStore* ds);
	~WriteReview();

	QPushButton* write;
	
private slots:
	void writeReview();
private:
	QVBoxLayout* overallLayout;

	QHBoxLayout* ratingLayout;
	QLabel* rating_label;
	QLineEdit* rating_;

	QHBoxLayout* yearLayout;
	QLabel* year_label;
	QLineEdit* year_;

	QHBoxLayout* monthLayout;
	QLabel* month_label;
	QLineEdit* month_;

	QHBoxLayout* dayLayout;
	QLabel* day_label;
	QLineEdit* day_;

	QHBoxLayout* textLayout;
	QLabel* text_label;
	QLineEdit* text_;

	QLabel* error;

	User* u_;
	Product* p_;
	MyDataStore* ds_;

};

#endif