#pragma once
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

template<class T>  // 使用泛型
class LinkedList
{
protected:
	unsigned int size;
	struct DataStruct {  // 用一个内部结构体保存数据和连接指针 
		T data;  // 数据
		DataStruct *next;  // 指向下一个的指针
	public:
		DataStruct(const T &a) : data(a), next(nullptr) {}  // 生成并初始化一个链表节点
		DataStruct(const T &a, DataStruct* const nextp)  // 生成一个带next指针的链表节点（用于链表插入）
			: data(a), next(nextp) {}
	};
	DataStruct *dataField;
public:
	LinkedList();  // 构造函数
	LinkedList(const std::vector<T>& arr);  // 用一个数组初始化链表
	LinkedList(const LinkedList<T>& another);  // 复制构造函数
	LinkedList<T>& operator= (const LinkedList<T>& another);  // 重载=号，与复制构造函数作用类似
	void insert(const T &a);  // 在链表尾部插入元素
	void insert(const T &a,int pos);  // 在指定位置插入元素
	void removeFirst(const T &a);  // 移除第一个给定的元素
	void removeAll(const T &a);  // 移除所有给定的元素
	void remove(int pos);  // 移除指定位置的元素
	void removeRange(T min, T max);  // 移除一个范围内的所有元素（要求元素类型重载了<号）
	void clear(void);  // 清空链表
	const T at(unsigned int pos);  // 返回第pos个元素的复制
	T& operator[] (unsigned int pos);  // 重载[]，返回第pos个元素的引用
	void print();  // 打印链表，方便调试
	LinkedList reverse();  // 反转链表，返回一个反转后的链表，原链表不变
	unsigned int find(const T &a);  // 找到第一个值为a的元素（要求元素类型重载了==号）
	unsigned int find(function<bool (T)> fun);  // 找到满足fun(a)=true的第一个a
	LinkedList merge(const LinkedList& another);  // 将两个链表合并
	bool empty(void) { return size == 0; }  // 判断是否为空
	unsigned int length(void) { return size; }  // 链表的长度
	~LinkedList();  // 析构函数
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
	while (i < pos - 1 && cursor != nullptr && cursor->next != nullptr) {
		i += 1;
		cursor = cursor -> next;
	}
	if (pos == 0)
		dataField = new DataStruct(a, dataField);
	else
		cursor->next = new DataStruct(a, cursor -> next);
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
	while (cursor->data >= min && cursor->data <= max) {
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
	cout << "链表内容为：";
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
