#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"
#include "LinearList.h"
#include "split.h"

char MENU[] = "��ѡ�������\n1)����Ԫ��\n2)ɾ��Ԫ��\n3)����Ԫ��\n4)��ת����\n5)�ϲ�����\n0)�����ϼ��˵�\n";
char INSERT_MENU[] = "����������Ԫ�غ�Ҫ�����λ�ã���ָ��λ������뵽���\n";
char DELETE_MENU[] = "��ѡ��ɾ�����ͺͲ������ð�Ƕ��Ÿ���\n1)ɾ����һ��ָ��ֵ��Ԫ��\n2)ɾ������ָ��ֵ��Ԫ��\n3)ɾ��ָ����Χ��Ԫ��\n";
char FIND_MENU[] = "������Ҫ���ҵ�Ԫ�أ��������Ԫ���������е�һ�γ��ֵ�λ��\n";


void testList(void)
{
	using namespace std;
	vector<int> arr = { 1, 3, 5, 7, 9};
	string cmd;
	vector<int> cmdN;
	bool quit = false;
	LinkedList<int> linkedList = LinkedList<int>(arr), newLinkedList;
	LinearList<int> linearList = LinearList<int>(arr), newLinearList;
	system("cls");
	do {
		system("cls");
		linkedList.print();
		linearList.print();
		cout << MENU;
		getline(cin, cmd);
		cmdN = split(cmd);
		system("cls");
		cout << "��ǰ������Ϊ��" << endl;
		linkedList.print();
		linearList.print();
		// system("pause");
		switch (cmdN[0]) {
		case 1:
			puts(INSERT_MENU);
			getline(cin, cmd);
			cmdN = split(cmd);
			if (cmdN.size() == 1) {
				linkedList.insert(cmdN[0]);
				linearList.insert(cmdN[0]);
			}
			else {
				linkedList.insert(cmdN[0], cmdN[1]);
				linearList.insert(cmdN[0], cmdN[1]);
			}
			cout << "�����Ԫ��Ϊ��" << endl;
			linkedList.print();
			linearList.print();
			system("pause");
			break;
		case 2:
			puts(DELETE_MENU);
			getline(cin, cmd);
			cmdN = split(cmd);
			switch (cmdN[0]) {
			case 1:
				puts("������ɾ����Ԫ��");
				getline(cin, cmd);
				cmdN = split(cmd);
				linkedList.removeFirst(cmdN[0]);
				linearList.removeFirst(cmdN[0]);
				break;
			case 2:
				puts("������ɾ����Ԫ��");
				getline(cin, cmd);
				cmdN = split(cmd);
				linkedList.removeAll(cmdN[0]);
				linearList.removeAll(cmdN[0]);
				break;
			case 3:
				puts("������ɾ����Ԫ�صķ�Χ");
				getline(cin, cmd);
				cmdN = split(cmd);
				linkedList.removeRange(cmdN[0], cmdN[1]);
				linearList.removeRange(cmdN[0], cmdN[1]);
				break;
			}
			cout << "ɾ�����Ԫ��Ϊ��" << endl;
			linkedList.print();
			linearList.print();
			system("pause");
			break;
		case 3:
			puts(FIND_MENU);
			getline(cin, cmd);
			cmdN = split(cmd);
			printf("�������У�%d ��һ�γ�����%d\n", cmdN[0],linkedList.find(cmdN[0]));
			printf("�����Ա��У�%d ��һ�γ�����%d\n", cmdN[0], linearList.find(cmdN[0]));
			system("pause");
			break;
		case 4:
			linkedList = linkedList.reverse();
			linearList = linearList.reverse();
			cout << "��ת�������Ϊ" << endl;
			linkedList.print();
			linearList.print();
			system("pause");
			break;
		case 5:
			puts("�����µ�����");
			getline(cin, cmd);
			cmdN = split(cmd);
			newLinkedList = LinkedList<int>(cmdN);
			newLinearList = LinearList<int>(cmdN);
			linkedList = linkedList.merge(newLinkedList);
			linearList = linearList.merge(newLinearList);
			cout << "�ϲ���ı�Ϊ��" << endl;
			linkedList.print();
			linearList.print();
			system("pause");
			break;
		case 0:
			quit = true;
			break;
		}
	} while (!quit);
}
