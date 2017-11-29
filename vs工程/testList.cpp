#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"
#include "LinearList.h"
#include "split.h"

char MENU[] = "请选择操作：\n1)插入元素\n2)删除元素\n3)查找元素\n4)反转链表\n5)合并链表\n0)返回上级菜单\n";
char INSERT_MENU[] = "请输入插入的元素和要插入的位置，不指定位置则插入到最后\n";
char DELETE_MENU[] = "请选择删除类型和参数，用半角逗号隔开\n1)删除第一个指定值的元素\n2)删除所有指定值的元素\n3)删除指定范围的元素\n";
char FIND_MENU[] = "请输入要查找的元素，返回这个元素在链表中第一次出现的位置\n";


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
		cout << "当前表内容为：" << endl;
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
			cout << "插入后元素为：" << endl;
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
				puts("请输入删除的元素");
				getline(cin, cmd);
				cmdN = split(cmd);
				linkedList.removeFirst(cmdN[0]);
				linearList.removeFirst(cmdN[0]);
				break;
			case 2:
				puts("请输入删除的元素");
				getline(cin, cmd);
				cmdN = split(cmd);
				linkedList.removeAll(cmdN[0]);
				linearList.removeAll(cmdN[0]);
				break;
			case 3:
				puts("请输入删除的元素的范围");
				getline(cin, cmd);
				cmdN = split(cmd);
				linkedList.removeRange(cmdN[0], cmdN[1]);
				linearList.removeRange(cmdN[0], cmdN[1]);
				break;
			}
			cout << "删除后的元素为：" << endl;
			linkedList.print();
			linearList.print();
			system("pause");
			break;
		case 3:
			puts(FIND_MENU);
			getline(cin, cmd);
			cmdN = split(cmd);
			printf("在链表中，%d 第一次出现在%d\n", cmdN[0],linkedList.find(cmdN[0]));
			printf("在线性表中，%d 第一次出现在%d\n", cmdN[0], linearList.find(cmdN[0]));
			system("pause");
			break;
		case 4:
			linkedList = linkedList.reverse();
			linearList = linearList.reverse();
			cout << "反转后的链表为" << endl;
			linkedList.print();
			linearList.print();
			system("pause");
			break;
		case 5:
			puts("输入新的链表");
			getline(cin, cmd);
			cmdN = split(cmd);
			newLinkedList = LinkedList<int>(cmdN);
			newLinearList = LinearList<int>(cmdN);
			linkedList = linkedList.merge(newLinkedList);
			linearList = linearList.merge(newLinearList);
			cout << "合并后的表为：" << endl;
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
