#include "writereview.h"
#include <stdlib.h>

using namespace std;


WriteReview::WriteReview(){
	setWindowTitle("Write a Review");
	overallLayout = new QVBoxLayout();

	ratingLayout = new QHBoxLayout();
	overallLayout->addLayout(ratingLayout);
	rating_label = new QLabel("Rating (1-5): ");
	ratingLayout->addWidget(rating_label);
	rating_ = new QLineEdit();
	ratingLayout->addWidget(rating_);

	yearLayout = new QHBoxLayout();
	overallLayout->addLayout(yearLayout);
	year_label = new QLabel("Year (2016-2030): ");
	yearLayout->addWidget(year_label);
	year_ = new QLineEdit();
	yearLayout->addWidget(year_);

	monthLayout = new QHBoxLayout();
	overallLayout->addLayout(monthLayout);
	month_label = new QLabel("Month (1-12): ");
	monthLayout->addWidget(month_label);
	month_ = new QLineEdit();
	monthLayout->addWidget(month_);

	dayLayout = new QHBoxLayout();
	overallLayout->addLayout(dayLayout);
	day_label = new QLabel("Day (1-31): ");
	dayLayout->addWidget(day_label);
	day_ = new QLineEdit();
	dayLayout->addWidget(day_);

	textLayout = new QHBoxLayout();
	overallLayout->addLayout(textLayout);
	text_label = new QLabel("Text: ");
	textLayout->addWidget(text_label);
	text_ = new QLineEdit();
	textLayout->addWidget(text_);

	write = new QPushButton("Write Review");
	connect(write, SIGNAL(clicked()), this, SLOT(writeReview()));
	overallLayout->addWidget(write);

	error = new QLabel("ERROR: Couldn't Write Review");
	error->hide();
	overallLayout->addWidget(error);

	setLayout(overallLayout);
	
}
void WriteReview::setWrite(User* u, Product* p, MyDataStore* ds){
	u_ = u;
	p_ = p;
	ds_ = ds;

}

WriteReview::~WriteReview(){
	delete overallLayout;

	delete ratingLayout;
	delete rating_label;
	delete rating_;

	delete yearLayout;
	delete year_label;
	delete year_;

	delete monthLayout;
	delete month_label;
	delete month_;

	delete dayLayout;
	delete day_label;
	delete day_;

	delete textLayout;
	delete text_label;
	delete text_;

	delete write;
	delete error;
}

//writes a review when clicked
void WriteReview::writeReview(){
	error->hide();
	if(rating_->text().isEmpty() || year_->text().isEmpty() ||
	 month_->text().isEmpty() || day_->text().isEmpty() ||
	 text_->text().isEmpty()) return;

	//gets texts
	int r = rating_->text().toInt();
	string y = year_->text().toStdString();
	string m = month_->text().toStdString();
	string d = day_->text().toStdString();
	string t = text_->text().toStdString();

	//changes back to no-text
	rating_->setText("");
	year_->setText("");
	month_->setText("");
	day_->setText("");
	text_->setText("");

	//error checking
	if(r < 1 || r > 5){
		error->show();
		return;
	}

	if(atoi(y.c_str()) < 2016 || atoi(y.c_str()) > 2030){
		error->show();
		return;
	}

	if(atoi(m.c_str()) < 1 ||  atoi(m.c_str()) > 12){
		error->show();
		return;
	}

	if(atoi(d.c_str()) < 1 || atoi(d.c_str()) > 31 ) {
		error->show();
		return;
	}


	if(m.size() == 1){
		m = "0" + m;
	}
	if(d.size() == 1){
		d = "0" + d;
	}
	string date = y + "-" + m + "-" + d;

	//adds the review
	Review* rev = new Review(p_->getName(),r, u_->getName(), date, t);
	ds_->addReview(rev);        
	this->hide();
}
