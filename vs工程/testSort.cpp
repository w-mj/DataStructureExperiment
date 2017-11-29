#include "LinearList.h"
#include "split.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
void testSort(void) {
	using namespace std;
	vector<int> v = { 1, 9, 5, 4, 3, 6, 7, 6, 4, 2, 0, 10 };
	LinearList<int> list(v);
	bool quit = false;
	string cmd;
	vector<int> cmdN;
	unsigned t;
	system("cls");
	while (!quit) {
		system("cls");
		// system("pause");
		cout << "请输入操作:\n1)输入一个数列\n2)运行快速排序\n3)运行二分查找\n0)返回上级菜单\n";
		getline(cin, cmd);
		system("cls");
		cmdN = split(cmd);
		if (cmdN.size() == 0)
			continue;
		switch (cmdN[0]) {
		case 1:
			cout << "输入一个数列" << endl;
			getline(cin, cmd);
			list = LinearList<int>(split(cmd));
			break;
		case 2:
			cout << "排序前的数列为 ";
			list.purePrint();
			list.sort();
			cout << "排序后的数列为 ";
			list.purePrint();
			system("pause");
			break;
		case 3:
			cout << "当前数列为 ";
			list.purePrint();
			cout << "输入要查找的元素" << endl;
			getline(cin, cmd);
			cmdN = split(cmd);
			t = list.biSearch(cmdN[0]);
			if (t < list.length())
				cout << "这个元素的索引为" << t << endl;
			else
				cout << "这个元素不存在" << endl;
			system("pause");
			break;
		case 0:
			quit = true;
			break;
		}
	}
	list.sort();
	list.print();
	cout << list.biSearch(7) << endl;
}