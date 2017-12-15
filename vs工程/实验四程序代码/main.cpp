void testSort(void);

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "split.h"
using namespace std;

int main(void) {
	char quit = false;
	string cmd;
	while (!quit) {
		system("cls");
		cout << "选择菜单:\n1)链表\n2)栈和队列\n3)树\n4)图\n5)排序\n0)退出\n";
		getline(cin, cmd);
		vector<int> cmdN = split(cmd);
		if (cmdN.size() == 0)
			continue;
		switch (cmdN[0]) {
		case 1:
			//testList();
			break;
		case 2:
			//testStack();
			break;
		case 3:
			//testTree();
			break;
		case 4:
			//testGraph();
			break;
		case 5:
			testSort();
			break;
		case 0:
			quit = true;
			break;
		default: 
			break;
		}
		
	}
	return 0;
}