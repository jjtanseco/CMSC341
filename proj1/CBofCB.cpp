// FILE: CBofCB.h
// AUTHOR: Joby Tanseco
// DATE: 9/25/2017
// SECTION: 5
// DESCRIPTION: This is the definition of the CBofCB class

#include <iostream>
#include <stdexcept>
#include "CBofCB.h"

using namespace std;



// default constructor
CBofCB::CBofCB(){
  m_buffers[0] = new InnerCB(10);
  for (int i = 1; i < m_obCapacity; i++){
    m_buffers[i] = NULL;
  }

  m_obSize = 1;
  m_oldest = 0;
  m_newest = 0;
  
}


// copy constructor
CBofCB::CBofCB(const CBofCB& other){
  m_obSize = other.m_obSize;
  m_oldest = other.m_oldest;
  m_newest = other.m_newest;
  for (int i = m_oldest; i < m_newest + 1; i = (i + 1) % m_obCapacity){
    m_buffers[i] = other.m_buffers[i];
  } 
}  


// destructor
CBofCB::~CBofCB(){
  for (int i = 0; i < m_obCapacity; i++){

    if (m_buffers[i] != NULL){
      delete m_buffers[i];
      m_buffers[i] = NULL;
    }

  }
}


// NAME: enqueue()
// PRE: Existing CBofCB, not full
// POST: data added to CBofCB 
// add item to this data structure
void CBofCB::enqueue(int data){
  if (isFull()){
    throw (overflow_error("Cannot add ANY more data"));
  }

  //adds new InnerCB if current CB is full
  if (m_buffers[m_newest]->isFull()){
    int lastSize = 2*(m_buffers[m_newest]->size());
    m_newest = (m_newest + 1) % m_obCapacity;

    if (m_buffers[m_newest] != NULL){
      delete m_buffers[m_newest];
      m_buffers[m_newest] = NULL;
    }

    m_buffers[m_newest] = new InnerCB(lastSize);
    m_obSize += 1;
  }

  m_buffers[m_newest]->enqueue(data);

}


// NAME: dequeue()
// PRE: Existing CBofCB, not empty
// POST: oldest data removed and returned
// remove item from this data structure
int CBofCB::dequeue(){
  //Checks if empty, throws error
  if (isEmpty()){
    throw (underflow_error("Completely empty CBofCB"));
  }

  else {
    //dequeues oldest item in current InnerCB
    int data = m_buffers[m_oldest]->dequeue();
    
    //moves m_oldest if its empty 
    if (m_buffers[m_oldest]->isEmpty()){
      
      if (m_buffers[m_oldest] != NULL){
	delete m_buffers[m_oldest];
	m_buffers[m_oldest] = NULL;
      }
      
      m_oldest = (m_oldest + 1) % m_obCapacity;
      m_obSize -= 1;
    }
  return data;
  }
}


// NAME: isFull();
// PRE: existing CBofCB
// POST: returns true if cannot add more items
bool CBofCB::isFull(){
  bool ends = ((m_newest == m_obCapacity) && (m_oldest == 0));
    if ((m_oldest == m_newest + 1) || ends){
      return ((m_buffers[m_newest]->isFull()) && 
	      (m_buffers[m_oldest]->isFull()));
    }
  return false;
}


// NAME: isEmpty()
// PRE: existing CBofCB
// POST: returns true if no items stored in data structure
bool CBofCB::isEmpty(){
  if (m_newest == m_oldest){
    return (m_buffers[m_newest]->isEmpty());
  }
  return false;
}


// NAME: size();
// PRE: existing CBofCB
// POST: returns number of items in the data structure as a whole.
// Note: not the number of InnerCB's
int CBofCB::size(){
  int size = 0;
  for (int i = m_oldest; i < m_newest; i = (i + 1) % m_obCapacity){
    size += (m_buffers[i]-> size());
  }
  if (m_oldest != m_newest){
    size += (m_buffers[m_oldest]-> size());
  }
  return size;
}


// overloaded assignment operator
const CBofCB& CBofCB::operator=(const CBofCB& rhs){
  m_obSize = rhs.m_obSize;
  m_oldest = rhs.m_oldest;
  m_newest = rhs.m_newest;

  //deletes data in m_buffers
  for (int i = 0; i < m_obCapacity; i++){
    if (m_buffers[i] != NULL){
      delete m_buffers[i];
      m_buffers[i] = NULL;
    }
  }

  //replaces m_buffers
  for (int i = m_oldest; i < m_newest + 1; i = (i + 1) % m_obCapacity){
    m_buffers[i] = rhs.m_buffers[i];
  }
  return * this;
}



// debugging function, prints out contents of data structure
void CBofCB::dump(){
  string line = "---------------------";
  cout << line << endl;
  cout << "Outer Circular buffer dump(), m_obSize = " 
       << m_obSize << ":" << endl;
  if (isEmpty()){
    cout << "Buffer is Empty." << endl;
  } else {

    int index = m_oldest;
    while (index != m_newest){
      cout << " [" << index << "] ";
      m_buffers[index]-> dump();
      index = (index + 1) % m_obCapacity;
      cout << endl;
    }
    cout << " [" << index << "] ";
    m_buffers[index] -> dump();
    cout << endl;
    cout << line << endl;
  }
}



