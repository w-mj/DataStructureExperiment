#pragma once
#include "LinkedList.h"
template <class T>
class Stack : protected LinkedList<T> {
public:
	Stack() : LinkedList() {}
	Stack(const Stack<T>& another): LinkedList(another) {}
	Stack<T>& operator=(const Stack<T>& another) {
		LinkedList::operator=(another);
	} 
	void push(const T& a) {
		LinkedList::insert(a, 0);
	}
	T top(void) {
		return LinkedList::at(0);
	}
	T pop(void) {
		T a = top();
		LinkedList::remove(0);
		return a;
	}
	void print(void);
	bool empty(void) { return LinkedList::empty(); }
	unsigned int size() { return LinkedList::length(); }
};

template<class T>
inline void Stack<T>::print(void) {
	std::cout << "Õ»µÄÄÚÈÝÎª£º";
	if (empty())
		std::cout << "¿Õ";
	else {
		LinkedList<T>::DataStruct *cursor = dataField;
		while (cursor != nullptr) {
			cout << cursor->data << " ";
			cursor = cursor->next;
		}
	}
	cout << endl;
}
