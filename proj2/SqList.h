// NAME: SqList.h
// AUTHOR: Joby Tanseco
// DATE: 9/30/2017
// SECTION: 5
// DESCRIPTION: This class defines a square list. 

#ifndef _SQLIST_H_
#define _SQLIST_H_

#include <iostream>
#include <list>
#include <stdexcept>
#include <cmath>

#include "Int341.h"

using namespace std;

class SqList{
public:
  SqList();
  SqList(const SqList& other);
  ~SqList();
  Int341 remove(int pos) ;
  void add(int pos, const Int341& data);
  void addFirst (const Int341& x);
  void addLast (const Int341& x);
  Int341 removeFirst (); //throw exceptions if empty
  Int341 removeLast ();
  int indexOf(const Int341& data);
  int numItems() ;
  void dump() ;
  void consolidate(); //called after insertion
  void inspector(); //Do not implement
  Int341& operator[](int pos) ;
  const SqList& operator=(const SqList& rhs);

  
private:
  list< list<Int341> > L;
  int m_items;
  
};

#endif