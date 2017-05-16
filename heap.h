#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

#include <string>
#include <iostream>


template <
typename T,
typename TComparator = std::equal_to<T>,
typename PComparator = std::less<double>,
typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );
    
    /// Destructor as needed
    ~Heap();
    
    /// Adds an item with the provided priority
    void push(double pri, const T& item);
    
    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;
    
    /// Removes the top element
    void pop();
    
    /// returns true if the heap is empty
    bool empty() const;
    
    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);
    
    
private:
    /// Add whatever helper functions you need below
    void trickleup(int i);
    void heapify(int i);
    
    
    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;
    
};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
                                             int m,
                                             const PComparator& c,
                                             const Hasher& hash,
                                             const TComparator& tcomp ) :

store_(),
m_(m),
c_(c),
keyToLocation_(100, hash, tcomp)

{
    
}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{
    
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    
    if(keyToLocation_.find(item) != keyToLocation_.end()){
        //std::cout << "duplicate item! (" << item << ")"<< std::endl;
        return;
    }
    store_.push_back(std::make_pair(priority, item));
    keyToLocation_.insert(std::make_pair(item, store_.size() - 1));
    trickleup(store_.size()-1);
    
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    
    if(empty()){
        throw std::logic_error("can't decreaseKey from empty heap");
    }
    else if(keyToLocation_.find(item) != keyToLocation_.end()){
        store_[keyToLocation_[item]].first = priority;
        trickleup(keyToLocation_[item]);
    }
    
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    
    //std::cout << "priority is " << store_[0].first << std::endl;
    return store_[0].second;
    
}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    store_[0] = store_.back();
    store_.pop_back();
    heapify(0);
    
    
}


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::heapify(int ind){
    //returns if child index doesnt exist (aka, it is a child already)
    if(ind * m_ + 1 > store_.size() || ind < 0) return;
    
    //finds the smallest child
    int small = ind * m_ + 1;
    for(int i = 2; i < m_ + 1; i++){
        if(ind * m_ + i < store_.size()){
            if(c_(store_[ind * m_ + i].first,store_[small].first)){
                small = ind * m_ + i;
            }
        }
        
    }
    
    //switch values if is "bigger" than child, continues on next node
    if(c_(store_[small].first, store_[ind].first)){
        std::pair<double, T> temp = store_[ind];
        store_[ind] = store_[small];
        store_[small] = temp;
        
        keyToLocation_[store_[ind].second] = ind;
        keyToLocation_[store_[small].second] = small;
        
        heapify(small);
    }
    
}


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleup(int i){
    int parent = (i-1)/m_;
    //looks if child is "less" than parent, continues too the top
    while(parent >= 0 && c_(store_[i].first, store_[parent].first) ){
        std::pair<double, T> temp = store_[parent];
        store_[parent] = store_[i];
        store_[i] = temp;
        
        keyToLocation_[store_[parent].second] = parent;
        keyToLocation_[store_[i].second] = i;
        
        i = parent;
        parent = (i - 1) / m_;
        
    }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const{
    return store_.empty();
}



#endif

