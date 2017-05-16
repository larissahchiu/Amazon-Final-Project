#ifndef MSORT_H
#define MSORT_H
#include <vector>
#include <iostream>
#include "product.h"
#include "review.h"

using namespace std;

struct AlphaStrComp
{
	bool operator() (const Product* lhs, const Product* rhs){
		return lhs->getName() < rhs->getName();
	}
	
};

struct PriceComp
{
	bool operator() (const Product* lhs, const Product* rhs){
		return lhs->getPrice() < rhs->getPrice();
	}	
};

struct ReviewComp
{
	bool operator() (const Product* lhs, const Product* rhs){
		return lhs->getAvg() > rhs->getAvg();
	}
	
};

struct DateComp
{
	bool operator() (const Review* lhs, const Review* rhs){
		return lhs->date > rhs->date;
	}
};

struct SuggestionComp
{
	bool operator()(const std::pair<std::string, double> lhs, const std::pair<std::string, double> rhs){
		if(lhs.second > rhs.second) return true;
		else if(lhs.second < rhs.second) return false;
		return lhs.first < rhs.first;
	}
};

template <class T, class Comparator>
void helper(std::vector<T>& myArray, int start, int end, Comparator comp);

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp){
    if(myArray.size() < 2) return;
    else helper(myArray, 0, myArray.size() - 1, comp);
}

template <class T, class Comparator>
void helper(std::vector<T>& myArray, int start, int end, Comparator comp){
	if(start >= end){
		return;
	}
	
	int middle = (start + end) / 2;
	helper(myArray, start, middle, comp);
	helper(myArray, middle + 1, end, comp);

	int s = start;
	int e = middle + 1;
	std::vector<T> output;

	while(s <= middle && e <= end){
		if(comp(myArray[s], myArray[e])){
			output.push_back(myArray[s]);
			s++;
		}
		else{
			output.push_back(myArray[e]);
			e++;
		}
	}

	while(s <= middle){
		output.push_back(myArray[s]);
		s++;
	}


	while(e <= end){
		output.push_back(myArray[e]);
		e++;
	}

	for(int i = start; i < end + 1; i++){
		myArray[i] = output[i-start];
	}
}

#endif

