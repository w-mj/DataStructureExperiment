void testList(void);
void testStack(void);
void testTree(void);
void testGraph(void);
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
	vector<int> cmdN;
	while (!quit) {
		system("cls");
		cout << "ѡ��˵�:\n1)����\n2)ջ�Ͷ���\n3)��\n4)ͼ\n5)����\n0)�˳�\n";
		getline(cin, cmd);
		cmdN = split(cmd);
		if (cmdN.size() == 0)
			continue;
		switch (cmdN[0]) {
		case 1:
			testList();
			break;
		case 2:
			testStack();
			break;
		case 3:
			testTree();
			break;
		case 4:
			testGraph();
			break;
		case 5:
			testSort();
			break;
		case 0:
			quit = true;
			break;
		}
		
	}
	return 0;
}