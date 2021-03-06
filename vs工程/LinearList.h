#pragma once
#include <vector>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;
template<class T>  // 泛型
class LinearList
{
private:
	unsigned int size;  // 当前元素数目
	unsigned int maxSize;  // 最大元素数目
	T *data;  // 保存数组的指针
	void expend(void);  // 扩容，当元素已满时可以自动扩容。
	void qsort(T*data, int s, int e, function<int (T, T)>);  // 快速排序的内部递归调用函数
public:
	LinearList();  // 构造函数
	LinearList(const std::vector<T>& arr);  // 用一个数组来初始化列表
	LinearList(const LinearList<T>& another);  //复制构造函数
	LinearList<T>& operator=(const LinearList<T>& another);  // 重载=号，作用与复制构造函数类似
	void insert(const T & a);  // 在末尾插入
	void insert(const T & a, int pos);  // 在指定位置插入
	void removeFirst(const T & a);  // 删除第一个指定的元素
	void removeAll(const T & a);  // 删除所有指定的元素
	void removeRange(T min, T max);  // 删除指定范围的元素怒
	void remove(const unsigned pos);  // 删除指定位置的元素
	int find(const T & a);  // 找到第一个指定的元素（顺序查找）
	unsigned length() { return size; }  // 线性表长度
	void print(void);  // 打印线性表，方便调试
	LinearList<T> merge(const LinearList<T> & another) const;  // 合并线性表，返回合并后的线性表
	LinearList<T> reverse(void) const;  // 反转表，返回反转后的线性表
	const T at(unsigned int pos) const; // 返回指定位置的值
	T& operator[](int pos);  // 返回指定位置的引用 
	bool empty() { return size == 0; } // 是否为空
	unsigned minPos();  //找到最小值的位置
	void sort(function<int(T, T)>);  // 快速排序，按照给定的函数顺序排序
	void sort() { sort(less<T>()); }  // 快速排序的一个重载，按照小于号排序
	unsigned biSearch(T a);  // 二分查找
	// void purePrint(void);  //
	~LinearList(); // 析构函数
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
LinearList<T> LinearList<T>::merge(const LinearList<T> & another)const  {
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
LinearList<T> LinearList<T>::reverse(void)const {
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
