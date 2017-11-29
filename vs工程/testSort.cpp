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
		cout << "���������:\n1)����һ������\n2)���п�������\n3)���ж��ֲ���\n0)�����ϼ��˵�\n";
		getline(cin, cmd);
		system("cls");
		cmdN = split(cmd);
		if (cmdN.size() == 0)
			continue;
		switch (cmdN[0]) {
		case 1:
			cout << "����һ������" << endl;
			getline(cin, cmd);
			list = LinearList<int>(split(cmd));
			break;
		case 2:
			cout << "����ǰ������Ϊ ";
			list.purePrint();
			list.sort();
			cout << "����������Ϊ ";
			list.purePrint();
			system("pause");
			break;
		case 3:
			cout << "��ǰ����Ϊ ";
			list.purePrint();
			cout << "����Ҫ���ҵ�Ԫ��" << endl;
			getline(cin, cmd);
			cmdN = split(cmd);
			t = list.biSearch(cmdN[0]);
			if (t < list.length())
				cout << "���Ԫ�ص�����Ϊ" << t << endl;
			else
				cout << "���Ԫ�ز�����" << endl;
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