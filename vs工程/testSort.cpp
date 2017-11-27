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
	system("cls");
	while (!quit) {
		system("cls");
		system("pause");
		cout << "���������:\n1)����һ������\n2)���п�������\n3)���ж��ֲ���\n0)�����ϼ��˵�\n";
		cin >> cmd;
		cmdN = split(cmd);
		if (cmdN.size() == 0)
			continue;
		switch (cmdN[0]) {
		case 1:
			cout << "����һ������" << endl;
			cin >> cmd;
			list = LinearList<int>(split(cmd));
			break;
		case 2:
			list.sort();
			break;
		case 3:
			cout << "����Ҫ���ҵ�Ԫ��" << endl;
			cin >> cmd;
			cmdN = split(cmd);
			cout << "���Ԫ����" << list.biSearch(cmdN[0]) << endl;
			break;
		case 4:
			quit = true;
			break;
		}
	}
	list.sort();
	list.print();
	cout << list.biSearch(7) << endl;
}