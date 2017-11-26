#pragma once
#include "LinkedList.h"
template <class T>
class Queue : protected LinkedList<T>{
public:
	Queue() : LinkedList() {};
	Queue(const Queue<T>& another) : LinkedList(another) {}
	void push(T a) {
		LinkedList<T>::insert(a);
	}
	T front(void) {
		return LinkedList<T>::at(0);
	}
	T pop(void) {
		T n = front();
		LinkedList<T>::remove(0);
		return n;
	}
	void print(void);
	bool empty(void) { return LinkedList<T>::empty(); }
	void clear(void) { LinkedList<T>::clear(); }
	unsigned int size(void) { return LinkedList<T>::length(); }
};

template<class T>
inline void Queue<T>::print(void)
{
	std::cout << "队列的内容为：";
	if (empty())
		std::cout << "空";
	else {
		LinkedList<T>::DataStruct *cursor = dataField;
		while (cursor != nullptr) {
			cout << cursor->data << " ";
			cursor = cursor->next;
		}
	}
	cout << endl;
}
