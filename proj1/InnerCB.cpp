// FILE: InnerCB.cpp
// AUTHOR: Joby Tanseco
// DATE: 9/24/2017
// SECTION: 5
// DESCRIPTION: This is the definition for the InnerCB class

#include <iostream>
#include <stdexcept>
#include "InnerCB.h"

using namespace std;


//Default constructor, size = 10
InnerCB::InnerCB(int n){
  m_capacity = n;
  m_buffer = new int[n];
  m_size = 0;
  m_start = 0;
  m_end = 0;
}


//Copy Constructor
InnerCB::InnerCB(const InnerCB& other){
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;

  
  m_buffer = new int[m_capacity];
  for (int i = 0; i < m_capacity; ++i){
    int index = (m_start + i) % m_capacity;
    m_buffer[index] = other.m_buffer[index];
  }
}


//Destructor
InnerCB::~InnerCB(){
  delete [] m_buffer;
}


// NAME: enqueue()
// PRE: existing buffer
// POST: item added to the end of buffer
void InnerCB::enqueue(int data){
  //checks if full
  if (isFull()){
    throw (overflow_error("Buffer is full."));
  }

  if (isEmpty()){
    m_buffer[m_end] = data;
  } else {
    //inserts data at the end. updates end
    int last = m_end + 1;
    m_end = last % m_capacity;
    m_buffer[m_end] = data;
  }
  m_size++;
}


// NAME: dequeue()
// PRE: existing queue with data
// POST: remove item from this data structure
int InnerCB::dequeue(){
  //checks if empty
  if (isEmpty()){
    throw underflow_error("Empty buffer.");
  } 

  //removes item at start, updates start
  int temp = m_buffer[m_start];
  m_start = (m_start + 1) % m_capacity;
  m_size = m_size - 1;
  return temp;
} 


// NAME: isFull()
// PRE: existing buffer
// POST: returns true if cannot add more items
bool InnerCB::isFull(){
  return (m_size == m_capacity);
}


// NAME: isEmpty()
// PRE: existing buffer
// POST: returns true if no items stored in data structure
bool InnerCB::isEmpty(){
  return (m_size == 0);
}


// NAME: capacity()
// PRE: existing InnerCB
// POST: returns m_capacity
int InnerCB::capacity(){
  return m_capacity;
}


// NAME: size()
// PRE: existing InnerCB
// POST: returns m_size
// number of items in the data structure as a whole.
int InnerCB::size(){
  return m_size;
}


// overloaded assignment operator
const InnerCB& InnerCB::operator=(const InnerCB& rhs){
  //clears buffer
  m_capacity = rhs.m_capacity;  
  delete [] m_buffer;
  m_buffer = NULL;
  //resizes buffer
  m_buffer = new int[m_capacity];
  m_start = rhs.m_start;
  m_end = rhs.m_end;
  m_size = rhs.m_size;
  int index = m_start;
  int end = (m_start + m_size) % m_capacity;
  //updates buffer data
  while (index != end){
    m_buffer[index] = rhs.m_buffer[index];
    index++;
  }
  m_buffer[index] = rhs.m_buffer[index];

  return * this;
}


// NAME: dump()
// PRE: existing innerCB
// POST: debugging function. Prints out contents.
void InnerCB::dump(){
  cout << " m_size = " << m_size << endl;
  if (isEmpty()){
    cout << "Buffer is Empty" << endl;
  } else {
    int index = m_start;
    while (index != m_end){
      cout << " [" << index << "] " << m_buffer[index];
      index = (index + 1) % m_capacity;
    }
    cout << " [" << index << "] " << m_buffer[index]; 
    cout << endl;
  }
}
