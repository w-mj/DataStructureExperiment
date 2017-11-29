#pragma once
#include <vector>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;
template<class T>
class LinearList
{
private:
	unsigned int size;
	unsigned int maxSize;
	T *data;
	void expend(void);
	void qsort(T*data, int s, int e, function<int (T, T)>);
public:
	LinearList();
	LinearList(const std::vector<T>& arr);
	LinearList(const LinearList<T>& another);
	LinearList<T>& operator=(const LinearList<T>& another);
	void insert(const T & a);
	void insert(const T & a, int pos);
	void removeFirst(const T & a);
	void removeAll(const T & a);
	void removeRange(T min, T max);
	void remove(const unsigned pos);
	int find(const T & a);
	unsigned length() { return size; }
	void print(void);
	LinearList<T> merge(const LinearList<T> & another);
	LinearList<T> reverse(void);
	const T at(unsigned int pos) const;
	T& operator[](int pos);
	bool empty() { return size == 0; }
	unsigned minPos();
	void sort(function<int(T, T)>);
	void sort() { sort(less<T>()); }
	unsigned biSearch(T a);
	void purePrint(void);
	~LinearList();
};

template<class T>
void LinearList<T>::expend(void) {
	T* newData = new T[2 * maxSize];
	memmove(newData, data, maxSize * sizeof(T));
	delete[] data;
	data = newData;
	maxSize *= 2;
}

template<class T>
inline void LinearList<T>::qsort(T * data, int st, int ed, function<int (T, T)> f)
{
	if (st >= ed - 1)
		return;
	int s = st, e = ed - 1;
	T mid = data[s];
	while (s < e) {
		while (s < e && f(mid, data[e]))
			e--;
		if (s < e)
			data[s++] = data[e];
		while (s < e && f(data[s], mid))
			s++;
		if (s < e)
			data[e--] = data[s];
	}
	data[s] = mid;
	qsort(data, st, s - 1, f);
	qsort(data, s + 1, ed, f);
}

template<class T>
LinearList<T>::LinearList() {
	size = 0;
	maxSize = 32;
	data = new T[maxSize];
}

template<class T>
LinearList<T>::LinearList(const vector<T>& arr) {
	maxSize = 1;
	while (maxSize < arr.size())
		maxSize *= 2;
	size = arr.size();
	data = new T[maxSize];
	memmove(data, arr.data(), size * sizeof(T));
}

template<class T>
inline LinearList<T>::LinearList(const LinearList<T>& another): size(0), data(nullptr) {
	operator=(another);
}

template<class T>
inline LinearList<T>& LinearList<T>::operator=(const LinearList<T>& another)
{
	size = another.size;
	maxSize = another.maxSize;
	if (data != nullptr)
		delete data;
	data = new T[maxSize * sizeof(T)];
	memmove(data, another.data, size * sizeof(T));
	return *this;
}

template<class T>
void LinearList<T>::insert(const T & a) {
	if (size == maxSize)
		expend();
	data[size++] = a;
}

template<class T>
void LinearList<T>::insert(const T & a, int pos) {
	if (size == maxSize)
		expend();
	int i = size;
	while (i > pos) {
		data[i] = data[i - 1];
		i -= 1;
	}
	size += 1;
	data[pos] = a;
}

template<class T>
void LinearList<T>::removeFirst(const T & a) {
	unsigned int i = 0;
	while (data[i] != a && i < size)
		i += 1;
	if (i < size)
		size -= 1;
	while (i < size) {
		data[i] = data[i + 1];
		i++;
	}
}

template<class T>
void LinearList<T>::removeAll(const T & a) {
	removeRange(a, a);
}

template<class T>
void LinearList<T>::removeRange(T min, T max) {
	unsigned int i = 0, step = 0;
	while (i < size - step) {
		data[i] = data[i + step];
		if (data[i] >= min && data[i] <= max)
			step += 1;
		else
			i += 1;
	}
	size -= step;
}

template<class T>
inline void LinearList<T>::remove(const unsigned pos)
{
	unsigned i = size - 1;
	while (i != pos) {
		data[i - 1] = data[i];
		i--;
	}
	size -= 1;
}

template<class T>
int LinearList<T>::find(const T & a)
{
	unsigned int i;
	for (i = 0; i < size; i++) {
		if (data[i] == a)
			break;
	}
	return i;
}

template<class T>
void LinearList<T>::print(void) {
	cout << "线性表内容：";
	for (unsigned int i = 0; i < size; i++)
		cout << data[i] << " ";
	cout << endl;
}

template<class T>
LinearList<T> LinearList<T>::merge(const LinearList<T> & another) {
	LinearList<T> result;
	unsigned int i = 0, j = 0;
	while (i < size && j < another.size)
		if (at(i) < another.at(j))
			result.insert(at(i++));
		else
			result.insert(another.at(j++));
	while (i < size)
		result.insert(at(i++));
	while (j < another.size)
		result.insert(another.at(j++));
	return result;
}

template<class T>
LinearList<T> LinearList<T>::reverse(void) {
	LinearList<T> result;
	for (int i = size - 1; i >= 0; i--)
		result.insert(at(i));
	return result;
}

template<class T>
const T LinearList<T>::at(unsigned int pos) const
{
	if (pos < 0)
		pos += size;
	if (pos >= size)
		throw "Out of range";
	return data[pos];
}

template<class T>
T & LinearList<T>::operator[](int pos)
{
	if (pos < 0)
		pos += size;
	if (pos >= size)
		throw "Out of range";
	return data[pos];
}

template<class T>
inline unsigned LinearList<T>::minPos()
{
	if (size == 0)
		throw "No elements";
	unsigned i = 0, minPos = 0;
	for (; i < size; i++) {
		if (data[i] < data[minPos])
			minPos = i;
	}
	return minPos;
}

template<class T>
inline void LinearList<T>::sort(function<int(T, T)> f)
{
	qsort(data, 0, size, f);
}

template<class T>
inline unsigned LinearList<T>::biSearch(T a)
{
	int s = 0, e = size - 1, mid;
	sort();
	while (s < e) {
		mid = (s + e) / 2;
		if (a < data[mid])
			e = mid - 1;
		else if (a > data[mid])
			s = mid;
		else
			return mid;
	}
	return size;
}

template<class T>
inline void LinearList<T>::purePrint(void)
{
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

template<class T>
LinearList<T>::~LinearList() {
	// TODO: delete data;
	// delete[] data;
}
