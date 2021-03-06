/* 
 * The following is an implementation of the Bag class, which is a data 
 * structure that simply collects a list of items whose internal 
 * representation or order does not really matter to the client. The Bag
 * data structure does not allow a client to remove items. A client 
 * can simply add items into the bag and when desired our client can also
 * iterate through the items in the bag. The following implementation uses
 * an linked list to internally store the items of the bag.
 *
 *
 * 
 * Author: Eliezer Abate
 * Last Edit: December 22, 2015
 * Irvine, CA
 *
 * Sources/Further Reading
 * -----------------------
 * For a further exposition on this data structure, refer to Introduction to 
 * Algorithms (Third Edition), Chapter 1.3, by Robert Sedgewick and Kevin
 * Wayne.
 */

#ifndef _LL_BAG_H
#define _LL_BAG_H

#include <iterator> 
#include <iostream>

/* node for linked list */
template<typename T>
struct Node {
  T data;
  Node *next;
};

/* forward declaration to allow use in BagIterator */
template<typename T>
class Bag;

template<typename T>
class BagIterator {
public:
  /* constructor */
  BagIterator (Node<T> *head,int pos): _pos(pos), _head(head) {}
  
  /* define != operator for Bag */
  bool operator != (BagIterator<T> other) {
  	 return _pos != other._pos;
  }

  bool operator == (BagIterator<T> other) {
  	 return _pos == other._pos;
  }

  /* overload ++ operator */
  BagIterator& operator++ () {
    ++_pos;
  	return *this; /* Is (*this) a BagIterator? Yes! */
  }

  /* overload the dereference * operator */
  /* We need to iterate through the local pointer _cur instead of _head because
   * on successive calls, the internal data member _head will not always point
   * to the head of the linked list. Thus, we ought to be careful in preserving
   * the original value and only traversing the elements with the pointer _cur 
   */
  T operator* () {
    Node<T> *_cur = _head;
    for(int i = 0; i < _pos; i++) {
      _cur = _cur->next;
    }
	  return _cur->data;
  }

private:
	int _pos; /* position */
  Node<T> *_head;
};

/* class declaration */
template<typename T>
class Bag {
  public:
  	Bag();
  	~Bag();
  	void add(T a); /* add an item to the bag */
  	bool isEmpty();
  	int size();
    BagIterator<T> begin() {
      return BagIterator<T>(head,0);
    }
    BagIterator<T> end() {
      return BagIterator<T>(head,count);
    }
  private:
  	int count;
  	Node<T> *head;
    Node<T> *tail;
};

/* 
 * Constructor
 * -----------
 * This constructor allocates memory for the initial internal array that will
 * store the Bag items. 
 */
template<typename T>
Bag<T>::Bag() {
	head = NULL;
  count = 0; /* initialize count */
}

/*
 * Destructor 
 * ----------
 */
template<typename T>
Bag<T>::~Bag() {
  Node<T> *cur = head;
  while(cur != NULL) {
     Node<T> *next = cur->next;
     delete cur;
     cur = next;
  }
}

/* 
 * Add
 * ---
 * This member function allows a client to add an item into the bag. 
 * Internally we add the new item to the front of the linked list.
 */
template<typename T>
void Bag<T>::add(T a) {
	 Node<T> *n = new Node<T>;
   n->data = a;
   /* add to front */
   n->next = head;
   head = n;
   count++;
}

/*
 * isEmpty
 * -------
 * Returns true if the Bag contains no items and false otherwise. 
 * 
 * Running Time:
 * The isEmpty() operation runs in constant O(1)
 */
 template <typename T>
 bool Bag<T>::isEmpty() {
 	return head == NULL;
 }

 /*
  * size
  * -----
  * Returns the number of items that are currently in the bag.
  *
  * Running Time:
  * O(1)
  */
  template <typename T>
  int Bag<T>::size() {
  	return count;
  }
#endif
