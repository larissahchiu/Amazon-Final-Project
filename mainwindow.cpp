#include "mainwindow.h"
#include <iomanip>

using namespace std;

MainWindow::MainWindow(MyDataStore* ds){

	//setWindowTitle("Amazon");
	ds_ = ds;
	wr_ = new WriteReview();
	cart_ = new Cart();

	//Overall Layout
	overallLayout = new QHBoxLayout();

	//User selection
	userLayout = new QVBoxLayout();
	overallLayout->addLayout(userLayout);

	/*user_label = new QLabel("Select User: ");
	userLayout->addWidget(user_label);

	user_list = new QListWidget();
	showUsers();
	connect(user_list, SIGNAL(currentRowChanged(int)), this, SLOT(selectUser(int)));
	userLayout->addWidget(user_list);*/


	//Extra Functionalies

	view_cart = new QPushButton("View Cart");
	connect(view_cart, SIGNAL(clicked()), this, SLOT(viewCart()));
	userLayout->addWidget(view_cart);

	view_database = new QPushButton("Create Database");
	connect(view_database, SIGNAL(clicked()), this, SLOT(viewDatabase()));
	userLayout->addWidget(view_database);

	logout = new QPushButton("Log Out");
	connect(logout, SIGNAL(clicked()), this, SLOT(logOut()));
	userLayout->addWidget(logout);

	quit = new QPushButton("Quit");
	connect(quit, SIGNAL(clicked()), this, SLOT(Quit()));
	userLayout->addWidget(quit);

	//Search
	productLayout = new QVBoxLayout();
	overallLayout->addLayout(productLayout);

	searchLayout = new QHBoxLayout();
	productLayout->addLayout(searchLayout);

	search_label = new QLabel("Search: ");
	searchLayout->addWidget(search_label);
	search_text = new QLineEdit();
	searchLayout->addWidget(search_text);

	AND = new QPushButton("AND");
	connect(AND, SIGNAL(clicked()), this, SLOT(searchAND()));
	searchLayout->addWidget(AND);
	OR = new QPushButton("OR");
	connect(OR, SIGNAL(clicked()), this, SLOT(searchOR()));
	searchLayout->addWidget(OR);

	search_by = new QHBoxLayout();
	productLayout->addLayout(search_by);
	search_by_label = new QLabel("Search By: ");
	search_by->addWidget(search_by_label);

	alpha = new QRadioButton("Alphabetically");
	connect(alpha, SIGNAL(clicked()), this, SLOT(searchbyAlpha()));
	search_by->addWidget(alpha);
	rating = new QRadioButton("High-Low Rating");
	connect(rating, SIGNAL(clicked()), this, SLOT(searchbyRating()));
	search_by->addWidget(rating);

	list_and_add = new QHBoxLayout();
	productLayout->addLayout(list_and_add);

    products_box = new QVBoxLayout();
    list_and_add->addLayout(products_box);
	product_label = new QLabel("Products: ");
	products_box->addWidget(product_label);
	products = new QListWidget();
	connect(products, SIGNAL(currentRowChanged(int)), this, SLOT(selectProduct(int)));
	products_box->addWidget(products);

	product_button_layout = new QHBoxLayout();
	products_box->addLayout(product_button_layout);

	view_reviews = new QPushButton("View Reviews");
	connect(view_reviews, SIGNAL(clicked()), this, SLOT(viewReviews()));
	product_button_layout->addWidget(view_reviews);
	add_to_cart = new QPushButton("Add to Cart");
	connect(add_to_cart, SIGNAL(clicked()), this, SLOT(addtoCart()));
	product_button_layout->addWidget(add_to_cart);
	write_review = new QPushButton("Write Review");
	connect(write_review, SIGNAL(clicked()), this, SLOT(writeReview()));
	connect(wr_->write, SIGNAL(clicked()), this, SLOT(viewReviews()));
	product_button_layout->addWidget(write_review);


	product_rec_button = new QPushButton("Product Recommendations");
	productLayout->addWidget(product_rec_button);
	connect(product_rec_button, SIGNAL(clicked()), this, SLOT(product_rec()));
	product_rec_list = new QListWidget();
	productLayout->addWidget(product_rec_list);
	product_rec_list->hide();


	review_layout = new QVBoxLayout();
	list_and_add->addLayout(review_layout);
	review_label = new QLabel("Reviews");
	review_layout->addWidget(review_label);
	reviews_list = new QListWidget();
	review_layout->addWidget(reviews_list);

	setLayout(overallLayout);


	loginBox = new QDialog();
	loginBox->setWindowTitle("Login");
	loginboxLayout = new QVBoxLayout();

	username_label = new QLabel("Enter username");
	loginboxLayout->addWidget(username_label);

	username_enter = new QLineEdit();
	loginboxLayout->addWidget(username_enter);

	password_label = new QLabel("Enter password");
	loginboxLayout->addWidget(password_label);

	password_enter = new QLineEdit("");
	password_enter->setEchoMode(QLineEdit::Password);
	loginboxLayout->addWidget(password_enter);

	login_button = new QPushButton("Login");
	loginboxLayout->addWidget(login_button);
	connect(login_button, SIGNAL(clicked()), this, SLOT(logIn()));
	add_user_button = new QPushButton("Add User");
	loginboxLayout->addWidget(add_user_button);
	connect(add_user_button, SIGNAL(clicked()), this, SLOT(createnewUser()));
	quit_user = new QPushButton("Quit");
	loginboxLayout->addWidget(quit_user);
	connect(quit_user, SIGNAL(clicked()), this, SLOT(Quit()));

	errormessage = new QMessageBox();
	loginBox->setLayout(loginboxLayout);


	product_rec_box = new QDialog();
	product_rec_box->setWindowTitle("Product Recommendations");
	product_rec_layout = new QVBoxLayout();
	product_rec_list = new QListWidget();
	product_rec_layout->addWidget(product_rec_list);
	QPushButton* done = new QPushButton("Done");
	product_rec_layout->addWidget(done);
	connect(done, SIGNAL(clicked()), this, SLOT(close_rec()));
	product_rec_box->setLayout(product_rec_layout);

	this->hide();
	loginBox->show();
}


MainWindow::~MainWindow(){
	delete userLayout;
	//delete user_label;
	//delete user_list;

	delete view_cart;
	delete view_database;
	delete logout;
	delete quit;

	delete searchLayout;
	delete search_label;
	delete search_text;
	delete AND;
	delete OR;

	delete search_by;
	delete search_by_label;
	delete alpha;
	delete rating;

	delete product_label;
	delete products;
	delete product_button_layout;
    delete view_reviews;
    delete add_to_cart;
	delete write_review;
    
    delete review_layout;
    delete review_label;
    delete reviews_list;

    delete products_box;
    delete list_and_add;
    delete productLayout;

    delete overallLayout;

    delete ds_;
  
}


/******** SLOTS ********/
//selects user and changes cart
void MainWindow::selectUser(int i){
	currUser = i;
	cart_->setCart(ds_->users_[currUser]);
}

//opens the cart
void MainWindow::viewCart(){
	if(ds_->users_.size() == 0) return;

	cart_->setCart(curr_user);
	cart_->show();
}

//writes to a file
void MainWindow::viewDatabase(){

	QString f = QFileDialog::getSaveFileName();

	string f_ = f.toStdString();

	ofstream ofile(f_.c_str());
    ds_->dump(ofile);
    ofile.close();


}

//quits program
void MainWindow::Quit(){
	QApplication::quit();
}

void MainWindow::logOut(){
	this->hide();
	loginBox->show();
}

//search based on AND
void MainWindow::searchAND(){
	if(search_text->text().isEmpty()){
		search_text->setText(""); 
		return;
	}

	//reads in keywords
	std::vector<string> search_terms;
	stringstream s1(search_text->text().toStdString());
	string t;
	while(s1 >> t){
		search_terms.push_back(convToLower(t));
	}

	found_products = ds_->search(search_terms, 0);

	products->clear();

	if(search == 1){
		searchbyRating();
	}
	//adds items to the found products list and updates listview
	else{
		for(unsigned int i = 0; i < found_products.size();i++){
		stringstream ss;
		ss << found_products[i]->getPrice();
		string s = ss.str();

		products->addItem(QString::fromStdString(found_products[i]->getName() + "\n"+ s));
	}

	}

	

	products->setCurrentRow(0);
	currProduct = 0;
	search_text->setText("");
}

//search based on OR
void MainWindow::searchOR(){
	if(search_text->text().isEmpty()){
		search_text->setText(""); 
		return;
	}

	//reads in keywords
	std::vector<string> search_terms;
	stringstream s1(search_text->text().toStdString());
	string t;
	while(s1 >> t){
		search_terms.push_back(convToLower(t));
	}

	found_products = ds_->search(search_terms, 1);
	products->clear();

	if(search == 1){
		searchbyRating();
	}

	//adds items to the found products list and updates listview
	else{
		for(unsigned int i = 0; i < found_products.size();i++){
		stringstream ss;
		ss << found_products[i]->getPrice();
		string s = ss.str();

		products->addItem(QString::fromStdString(found_products[i]->getName() + "\n"+ s));
		}

	}


	products->setCurrentRow(0);
	currProduct = 0;
	search_text->setText("");
	
}

//sorts based on alphabetical
void MainWindow::searchbyAlpha(){
	//merge sort
	AlphaStrComp comp1;
	mergeSort(found_products, comp1);

	products->clear();

	//clears list and updates the list
	for(unsigned int i = 0; i < found_products.size();i++){
		stringstream ss;
		ss << found_products[i]->getPrice();
		string s = ss.str();

		products->addItem(QString::fromStdString(found_products[i]->getName() + "\n"+ s));
	}
	products->setCurrentRow(0);
	currProduct = 0;
	search = 0;
	
}


//sorts based on rating
void MainWindow::searchbyRating(){
	//merge sort
	ReviewComp comp3;
	mergeSort(found_products, comp3);

	products->clear();

	//clears list and updates the list
	for(unsigned int i = 0; i < found_products.size();i++){
		stringstream ss;
		ss << found_products[i]->getPrice();
		string s = ss.str();

		products->addItem(QString::fromStdString(found_products[i]->getName() + "\n"+ s));
	}
	products->setCurrentRow(0);
	currProduct = 0;
	search = 1;
	
}

//selects product index
void MainWindow::selectProduct(int i){
	currProduct = i;
	reviews_list->clear();
	review_label->setText("Reviews");
	
}

//looks at the reviews of the selected product
void MainWindow::viewReviews(){
	if(found_products.size() == 0) return;
	reviews_list->clear();

	DateComp comp4;
	mergeSort(found_products[currProduct]->reviews_, comp4);
	for(unsigned int i = 0; i < found_products[currProduct]->reviews_.size(); i++){
		reviews_list->addItem(QString::fromStdString(found_products[currProduct]->reviews_[i]->rating_to_string() + "\n" + 
			found_products[currProduct]->reviews_[i]->username + "\n" + 
			found_products[currProduct]->reviews_[i]->date + "\n" + 
			found_products[currProduct]->reviews_[i]->reviewText + "\n"));
	}

	review_label->setText("Reviews for " + QString::fromStdString(found_products[currProduct]->getName()));
}

//adds to cart based on user and product selected
void MainWindow::addtoCart(){
	if(found_products.size() == 0) return;

	cart_->setCart(curr_user);
	curr_user->addToCart(found_products[currProduct]);
	cart_->updateCart();
}

//writes a review bassed on user and product selected
void MainWindow::writeReview(){
	if(found_products.size() == 0) return;

	for(unsigned int i = 0; i < curr_user->reviews_.size(); i++){
		if(curr_user->reviews_[i]->prodName == found_products[currProduct]->getName()){
			errormessage->setText("Already wrote a review for selected product!");
			errormessage->show();
			return;
		}
	}

	wr_->setWrite(curr_user, found_products[currProduct], ds_);

	wr_->show();

}

//Login given user exists and password is correct
void MainWindow::logIn(){
	//checks to see that both fields have been filled
	if(username_enter->text().isEmpty() || password_enter->text().isEmpty()){
		username_enter->setText("");
		password_enter->setText("");
		return;
	}

	string name = username_enter->text().toStdString();
	string pass = password_enter->text().toStdString();

	curr_user = ds_->find_user(name);

	//User does not exist
	if(curr_user == NULL){
		errormessage->setText("Not a User");
		errormessage->exec();
		username_enter->setText("");
		password_enter->setText("");
		return;
	}
	//Password is too long to hash
	if(pass.size() > 8){
		errormessage->setText("Password is too long");
		errormessage->exec();
		username_enter->setText("");
		password_enter->setText("");
		return;
	}
	//Password is incorrect
	if(curr_user->getPassword() != hash(pass)){
		errormessage->setText("Wrong Password");
		errormessage->exec();
		username_enter->setText("");
		password_enter->setText("");
		return;
	}
	//Password is correct
	else{
		username_enter->setText("");
		password_enter->setText("");
		loginBox->hide();
		this->show();
		setWindowTitle("Welcome to Amazon, " + QString::fromStdString(curr_user->getName()) + "!\n");
	}
}

void MainWindow::createnewUser(){
	//checks to see if both fields are filled
	if(username_enter->text().isEmpty() || password_enter->text().isEmpty()){
		username_enter->setText("");
		password_enter->setText("");
		return;
	}
	string name = username_enter->text().toStdString();
	string pass = password_enter->text().toStdString();

	//sees if the username is unique
	if(ds_->find_user(name) != NULL){
		errormessage->setText("User already exists");
		errormessage->exec();
		username_enter->setText("");
		password_enter->setText("");
		return;
	}

	//sees if the password is short enough
	if(pass.size() > 8){
		errormessage->setText("Password is too long");
		errormessage->exec();
		username_enter->setText("");
		password_enter->setText("");
		return;
	}

	//creates new user
	curr_user = new User(name, 100, 0, hash(pass));
	ds_->addUser(curr_user);

	loginBox->hide();
	this->show();
	setWindowTitle("Welcome to Amazon, " + QString::fromStdString(curr_user->getName()));
}

void MainWindow::product_rec(){

	//Calculate Basic Similarities: find set intersection between between all pairs of users
	//similarities will vary between 0-1 (max to no similarity). Then for each of the products rated
	//compute, the similarity between each item (abs(a-b)/ 4), the basic similarity between the two users
	//should be the average of all the similarities. 

	std::map<std::string, std::vector<std::pair<std::string, double> > > graph;
	for(unsigned int i = 0; i < ds_->users_.size(); i++){
		std::vector<std::pair<std::string, double> > a_list;

		for(unsigned int j = 0; j < ds_->users_.size(); j++){
			if(i != j){
				User* u1 = ds_->users_[i];
				User* u2 = ds_->users_[j];

				set<Product*> set_itersection;
				double basic = 0;
				//finds the set intersection of reviews between the users
				for(unsigned int x = 0; x < u1->reviews_.size(); x++){
					for(unsigned int y = 0; y < u2->reviews_.size(); y++){
						if(u1->reviews_[x]->prodName == u2->reviews_[y]->prodName){
							set_itersection.insert((ds_->find_product(u1->reviews_[x]->prodName)));
							basic = basic + abs(u1->reviews_[x]->rating - u2->reviews_[y]->rating) / 4.0;
						}
					}
				}

				if(set_itersection.size() != 0){
					basic = basic / set_itersection.size();
					std::pair<std::string, double> p(ds_->users_[j]->getName(), basic);
					a_list.push_back(p);
				}

			}
		}

		graph.insert(std::make_pair(ds_->users_[i]->getName(), a_list));
	}

	

	//Refune Similarity Estimate: between each pairs of users, we have an an edge with the weight is 
	//the "basic similarity", perform dijkstras alg in order to find shortest path from starting node
	//to rest of the graph, updates the similarites to a shorter path

	for(unsigned int i = 0; i < ds_->users_.size(); i++){
		ds_->users_[i]->dist = 1.0;

	}

	Heap<std::string> h(2);
	curr_user->dist = 0;
	curr_user->pred = NULL;
	h.push(curr_user->dist, curr_user->getName());


	for(unsigned int i = 0; i < ds_->users_.size(); i++){
		if(ds_->users_[i]->getName() != curr_user->getName()){
			ds_->users_[i]->dist = 1;
			h.push(ds_->users_[i]->dist, ds_->users_[i]->getName());
		}
	}


	while(!h.empty()){
		std::string v = h.top();
		h.pop();
		for(unsigned int i = 0; i < graph[v].size(); i++){
			User* u = ds_->find_user(graph[v][i].first);
			double weight = graph[v][i].second;
			if(ds_->find_user(v)->dist + weight < u->dist){
				u->pred = ds_->find_user(v);
				u->dist = ds_->find_user(v)->dist + weight;
				h.decreaseKey(u->dist, u->getName());
			}

		}
	}

	std::ofstream ofile("rec.txt");
	ofile << curr_user->getName() << std::endl;


	//if the reviews of the current user are equal to the number of products, then no recommended products
	if(curr_user->reviews_.size() == ds_->products_.size()){
		product_rec_list->addItem("No Recommendations Found!");
		product_rec_box->show();
		ofile << "No Recommendations Found!" << endl;
		return;
	}

	//otherwise, there is some number of recommendations
	std::vector<std::pair<std::string, double> > recommendations = ds_->makeSuggestion(curr_user->getName());

	//sorts throught merge sort
	SuggestionComp comp;
	mergeSort(recommendations, comp);

	product_rec_list->clear();

	//populates list and file 
	for(unsigned int i = 0; i < recommendations.size(); i++){

		if(ds_->userstoReviews_[recommendations[i].first].size() == 0) continue;
		double x = floor(recommendations[i].second * 100 + 0.5) / 100;

		product_rec_list->addItem(QString::fromStdString(recommendations[i].first + "   ") +  QString::number(x));
		ofile << x <<  " " << recommendations[i].first << endl;
	}

	if(product_rec_list->count() == 0){
		product_rec_list->addItem("No Recommendations Found!");
		ofile << "No Recommendations Found!" << endl;
	}

	product_rec_box->show();

}

void MainWindow::close_rec(){
	product_rec_box->close();
}



/******** OTHER FUNCTIONS ********/

//displays user
void MainWindow::showUsers(){
	/*for(unsigned int i = 0; i < ds_->users_.size(); i++){

		user_list->addItem(QString::fromStdString(ds_->users_[i]->getName()));
	}
	user_list->setCurrentRow(0);
	currUser = 0;*/

	
}

int MainWindow::hash(string p){
	long long int p1 = 0;
	for(unsigned int i=0; i<p.length(); i++){
		p1 += (long long) pow(128, i) * p[p.length()-i-1];
	}

	unsigned int array [4];

	for(int i = 0; i < 4; i++){
		array[3-i] = p1 % 65521;
		p1 = p1 / 65521;
	}

	int hashpass = ((45912*array[0]) + (35511*array[1]) + (65169*array[2]) + (4625*array[3])) % 65521;

	return hashpass;

}


