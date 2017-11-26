#pragma once
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

template<class T>
class LinkedList
{
protected:
	unsigned int size;
	struct DataStruct {
		T data;
		DataStruct *next;
	public:
		DataStruct(const T &a) : data(a), next(nullptr) {}
		DataStruct(const T &a, DataStruct* const nextp)
			: data(a), next(nextp) {}
	};
	DataStruct *dataField;
public:
	LinkedList();
	LinkedList(const std::vector<T>& arr);
	LinkedList(const LinkedList<T>& another);
	LinkedList<T>& operator= (const LinkedList<T>& another);
	void insert(const T &a);
	void insert(const T &a,int pos);
	void removeFirst(const T &a);
	void removeAll(const T &a);
	void remove(int pos);
	void removeRange(T min, T max);
	void clear(void);
	const T at(unsigned int pos);
	T& operator[] (unsigned int pos);
	void print();
	LinkedList reverse();
	unsigned int find(const T &a);
	unsigned int find(function<bool (T)> fun);
	LinkedList merge(const LinkedList& another);
	bool empty(void) { return size == 0; }
	unsigned int length(void) { return size; }
	~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList() {
	size = 0;
	dataField = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const vector<T>& arr) {
	size = arr.size();
	vector<T>::const_iterator iter = arr.begin();
	dataField = new DataStruct(*iter++);
	DataStruct *cursor = dataField;
	while (iter != arr.end()) {
		cursor->next = new DataStruct(*iter++);
		cursor = cursor->next;
	}
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& another) {
	operator=(another);
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& another)
{
	size = another.size;
	if (size != 0) {
		dataField = new DataStruct(another.dataField->data);
		DataStruct *anotherCursor = another.dataField, *cursor = dataField;
		while (anotherCursor->next != nullptr) {
			cursor->next = new DataStruct(anotherCursor->next->data);
			cursor = cursor->next;
			anotherCursor = anotherCursor->next;
		}
	}
	return *this;
}

template<class T>
void LinkedList<T>::insert(const T &a) {
	DataStruct* cursor = dataField;
	if (dataField == nullptr)
		dataField = new DataStruct(a);
	else {
		while (cursor->next != nullptr)
			cursor = cursor -> next;
		cursor->next = new DataStruct(a);
	}
	size += 1;
}

template<class T>
void LinkedList<T>::insert(const T &a, int pos) {
	int i = 0;
	DataStruct* cursor = dataField;
	while (i < pos && cursor->next != nullptr) {
		i += 1;
		cursor = cursor -> next;
	}
	if (pos == 0)
		dataField = new DataStruct(a, dataField);
	else
		cursor->next = new DataStruct(a, cursor);
	size += 1;
}

template<class T>
void LinkedList<T>::removeFirst(const T &a) {
	DataStruct* cursor = dataField, *del;
	if (cursor->data == a) {
		dataField = cursor->next;
		delete cursor;
		size -= 1;
		return;
	}
	while (cursor->next != nullptr && cursor->next->data != a)
		cursor = cursor -> next;
	if (cursor->next == nullptr)
		throw "No such item";
	del = cursor->next;
	cursor->next = del->next;
	delete del;
	size -= 1;
}

template<class T>
void LinkedList<T>::removeAll(const T &a) {
	removeRange(a, a);
}

template<class T>
void LinkedList<T>::remove(int pos) {
	if (pos < 0)
		pos += size;
	if (pos > (int)size - 1)
		throw "Out of range";
	DataStruct *cursor = dataField, *del;
	for (int i = 0;pos != 0 && i < pos - 1; i++)
		cursor = cursor -> next;
	if (pos == 0) {
		dataField = cursor->next;
		delete cursor;
	}
	else {
		del = cursor->next;
		cursor->next = del->next;
		delete del;
	}
	size -= 1;
}

template<class T>
void LinkedList<T>::removeRange(T min, T max) {
	DataStruct* cursor = dataField, *del;
	if (cursor->data >= min && cursor->data <= max) {
		dataField = cursor->next;
		delete cursor;
		cursor = dataField;
		size -= 1;
	}
	while (cursor->next != nullptr) {
		if (cursor->next->data >= min && cursor->next->data <= max) {
			del = cursor->next;
			cursor->next = del->next;
			delete del;
			size -= 1;
		}
		else {
			cursor = cursor -> next;
		}
	}
}

template<class T>
inline void LinkedList<T>::clear(void)
{
	while (size > 0)
		remove(0);
}

template<class T>
const T LinkedList<T>::at(unsigned int pos)
{
	if(size == 0 || pos > size - 1)
		throw "Out of Range";
	DataStruct* cursor = dataField;
	for (unsigned int i = 0; i < pos; i++)
		cursor = cursor -> next;
	return cursor->data;
}

template<class T>
T& LinkedList<T>::operator[](unsigned int pos)
{
	DataStruct* cursor = dataField;
	for (unsigned int i = 0; i < pos; i++)
		cursor = cursor -> next;
	return cursor->data;
}

template<class T>
void LinkedList<T>::print()
{
	DataStruct* cursor = dataField;
	cout << "Á´±íÄÚÈÝÎª£º";
	while (cursor != nullptr) {
		cout << cursor->data << " ";
		cursor = cursor -> next;
	}
	cout << endl;
}

template<class T>
LinkedList<T> LinkedList<T>::reverse()
{
	LinkedList<T> result;
	DataStruct* cursor = dataField;
	while (cursor != nullptr) {
		result.insert(cursor->data, 0);
		cursor = cursor->next;
	}
	return result;
}

template<class T>
unsigned int LinkedList<T>::find(const T &a)
{
	return find([&](const T& b) {return a == b; });
}

template<class T>
unsigned int LinkedList<T>::find(function<bool (T)> fun) {
	int i = 0;
	DataStruct *cursor = dataField;
	while (cursor != nullptr && fun(cursor -> data) == false) {
		cursor = cursor->next;
		i += 1;
	}
	return i;
}

template<class T>
LinkedList<T> LinkedList<T>::merge(const LinkedList & another)
{
	LinkedList<T> result;
	DataStruct *cursor1 = dataField, *cursor2 = another.dataField;
	while (cursor1 != nullptr && cursor2 != nullptr) {
		if (cursor1->data < cursor2->data) {
			result.insert(cursor1->data);
			cursor1 = cursor1->next;
		}
		else {
			result.insert(cursor2->data);
			cursor2 = cursor2->next;
		}
	}
	while (cursor1 != nullptr) {
		result.insert(cursor1->data);
		cursor1 = cursor1->next;
	}
	while (cursor2 != nullptr) {
		result.insert(cursor2->data);
		cursor2 = cursor2->next;
	}
	return result;
}


template<class T>
LinkedList<T>::~LinkedList() {
	DataStruct *cursor = dataField, *del;
	while (cursor != nullptr) {
		del = cursor;
		cursor = cursor->next;
		delete del;
	}
}
