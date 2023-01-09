// NAME: SqList.cpp
// AUTHOR: Joby Tanseco
// DATE: 9/30/2017
// SECTION: 5
// DESCRIPTION: THIS IS THE IMPLEMENTATION OF THE SqList class.

#include "SqList.h"

//default constructor
SqList::SqList(){
  list <Int341> temp;
  L.push_back(temp);
  m_items = 0;
}

//destructor(not really needed)
SqList::~SqList(){
  L.clear();
}

//copy constructor
SqList::SqList(const SqList& other): L(other.L){ m_items = other.m_items;}


// NAME: remove()
// PRE: existing SqList containing data
// POST: data removed and returned
Int341 SqList::remove(int pos){
  //iterates through outer List to find which inner has the position
  int counter = 0;
  int currentSize; //current size;
  list<list<Int341> >::iterator outer = L.begin();

  currentSize = outer-> size(); // saves size of the current list
  counter += outer-> size();

  while(counter < pos){
    ++outer;
    currentSize = outer-> size(); // saves size of the current 
    counter += outer-> size();
  }
  
  int innerPos = currentSize - (counter - pos); //position within the inner list;
  //sets iterator to position
  list<Int341>::iterator inner = outer-> begin();
  for (int i = 0; i < innerPos; i++){
    ++inner;
  }
  Int341 temp = *inner;
  outer->erase(inner); //removes data;
  return temp; //returns temp
  m_items--;
} 


// NAME: add()
// PRE: existing SqList
// POST: data inserted into list
void SqList::add(int pos, const Int341& data){
    //iterates through outer List to find which inner has the position
  int counter = 0;
  int currentSize; //current size;
  list<list<Int341> >::iterator outer = L.begin();

  currentSize = outer-> size(); // saves size of the current list
  counter += outer-> size();

  while(counter < pos){
    ++outer;
    currentSize = outer-> size(); // saves size of the current 
    counter += outer-> size();
  }
  
  int innerPos = currentSize - (counter - pos); //position within the inner list;
  //sets iterator to position
  list<Int341>::iterator inner = outer-> begin();
  for (int i = 0; i < innerPos; i++){
    ++inner;
  }
  outer->insert(inner, data); //inserts data
  m_items++;
}


// NAME: addFirst()
// PRE: existing SqList
// POST: item added to beginning of list
void SqList::addFirst (const Int341& x){
  L.front().push_front(x);
  m_items++;
  consolidate();
}


// NAME: addLast()
// PRE: existing SqList
// POST: item added to the end of list
void SqList::addLast (const Int341& x){
  L.back().push_back(x);
  m_items++;
  consolidate();
}


// NAME: removeFirst()
// PRE: SqList containing items
// POST: removes the first item, consolidates
Int341 SqList::removeFirst (){ //throw exceptions if empty
  Int341 temp;
  //throws error if empty
  if (L.empty()){
    throw out_of_range("Empty List");
  } else{
    //deletes front item
    temp = L.front().front();
    L.front().pop_front();
  }
  m_items++;
  consolidate();
  return temp; //returns value
}


// NAME: removeLast()
// PRE: SqList containing items
// POST: last item removed, consolidate called
Int341 SqList::removeLast (){
  Int341 temp;  
  //throws error if empty
  if(L.empty()){ 
    throw out_of_range("Empty List");
  }else {
    //deletes last item
    temp = L.back().back();
    L.back().pop_back();
  }
  m_items--;
  consolidate();
  return temp; //returns value
}


// NAME: indexOf()
// PRE: existing SqList() containing items
// POST: returns first index containing data
int SqList::indexOf(const Int341& data){
  Int341 temp;
  for (list<list<Int341> >::iterator outer = L.begin(); outer != L.end(); ++outer){
    int counter = 0;
    for (list<Int341>::iterator inner = outer->begin(); inner != outer->end(); ++inner){
      if (data.m_data == inner->m_data){
        return counter;
      }
      ++counter;
    }
  }
  return -1;
}


// NAME: numItems()
// PRE: existing SqList
// POST: returns the number of items
int SqList::numItems(){
  return m_items;
}


// NAME: dump();
// PRE: existing SqList
// POST: prints dump
void SqList::dump(){
  string line = "-----------------------";
  cout << "---- SqList dump() ----" << endl;
  cout << line << endl;
  int count = 0;
  for (list<list<Int341> >::iterator outer = L.begin(); outer != L.end(); ++outer){
    cout << count << " (" << outer->size() << ") : ";
    list<Int341> temp = *outer;
    for (list<Int341>::iterator inner = temp.begin(); inner != temp.end(); ++inner){
      cout << inner->m_data << " ";
    }
    cout << endl;
    count++;
  }
  cout << line << endl;
}


// NAME: consolidate()
// PRE: existing SqList containing data
// POST: SqList consolidated. large lists are split and small lists are merged.
void SqList::consolidate(){ //called after insertion
  int items = numItems();
  unsigned int small = (sqrt(items))/2;
  unsigned int big = 2 * (sqrt(items));
  list<list<Int341> >::iterator outer;
  list<list<Int341> >::iterator next = L.begin();
  next++;
  for (outer = L.begin(); outer != L.end(); ++outer){
    //checks if list is empty
    if (outer->empty()){
      outer = L.erase(outer);
    }else if(outer->size() >= big){ //checks if list is too big
      list<Int341> temp;
      //finds halfway point of outer
      list<Int341>::iterator inEnd = outer->begin();
      for (unsigned int i = 0; i < (outer->size())/2; i++){
        ++inEnd;
      }
      ++inEnd;
      //puts half of data into temp
      temp.splice(temp.begin(), *outer, outer->begin(), inEnd);
      L.insert(outer, temp);
     //combines lists if too small 
    }else {
      list<list<Int341> >::iterator next = outer;
      next++;
      if(next == L.end()){
        break;
      }
      else{
        if(outer->size() <= small && next->size() <= small){
          list<Int341>::iterator last = outer->end();
          last--;
          next->splice(next->end(), *outer, outer->begin(), last/*outer->end()*/);
        }
      }
    }
  }
  /*
  //consolidates last list
  if (outer->empty()){
    L.erase(outer);
  }else if(outer->size() >= big){ //checks if list is too big
    list<Int341> temp;
    //finds halfway point of outer
    list<Int341>::iterator inEnd = outer->begin();
    for (unsigned int i = 0; i < (outer->size())/2; i++){
      ++inEnd;
    }
    ++inEnd;
    //puts half of data into temp
    temp.splice(temp.begin(), *outer, outer->begin(), inEnd);
    L.insert(outer, temp);
  }
  */
}


// overloaded access operator
Int341& SqList::operator[](int pos){
  //iterates through outer List to find which inner has the position
  int counter = 0;
  int currentSize; //current size;
  list<list<Int341> >::iterator outer = L.begin();

  currentSize = outer-> size(); // saves size of the current list
  counter += outer-> size();

  while(counter < pos){
    ++outer;
    currentSize = outer-> size(); // saves size of the current 
    counter += outer-> size();
  }
  
  int innerPos = currentSize - (counter - pos); //position within the inner list;
  //sets iterator to position
  list<Int341>::iterator inner = outer-> begin();
  for (int i = 0; i < innerPos; i++){
    ++inner;
  }
  return *inner;
}


//overloaded assignment operator
const SqList& SqList::operator=(const SqList& rhs){
  L.clear();
  L = rhs.L;
  return *this;
}

//void inspector(){} //Do not implement

