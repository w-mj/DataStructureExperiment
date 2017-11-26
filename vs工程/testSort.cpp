#include "LinearList.h"
void testSort(void) {
	vector<int> v = { 1, 9, 5, 4, 3, 6, 7, 6, 4, 2, 0, 10 };
	LinearList<int> list(v);
	list.sort();
	list.print();
	cout << list.biSearch(7) << endl;
}