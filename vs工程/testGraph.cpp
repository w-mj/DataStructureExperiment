#include "MatrixGraph.h"
#include "ListGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include "split.h"

void testGraph(void) {
	using namespace std;
	MatrixGraph graph;
	ListGraph lgraph;
	bool quit = false;
	string cmd;
	vector<int> cmdN;
	vector<unsigned> tm;
	while (!quit) {
		cout << "���������\n1)����һ��ͼ\n2)����AOV����\n3)����AOE�ؼ�·��\n4)��Dijkstra���·��\n0)�����ϼ��˵�\n";
		cin >> cmd;
		cmdN = split(cmd);
		switch (cmdN[0]) {
		case 1:
			while (!quit) {
				cout << "1)��ӵ�\n2)��ӱߣ��������صĵ㲻���ڻ��Զ�������\n0)�����ϼ�\n";
				cin >> cmd;
				cmdN = split(cmd);
				switch (cmdN[0]) {
				case 1:
					cout << "������Ȩ�أ�Ĭ��Ȩ��Ϊ1��" << endl;
					cin >> cmd;
					cmdN = split(cmd);
					if (cmdN.size() == 1) {
						graph.addVertex(cmdN[0], 1);
						lgraph.addVertex(cmdN[0], 1);
					}
					else if (cmdN.size() == 1) {
						graph.addVertex(cmdN[0], cmdN[1]);
						lgraph.addVertex(cmdN[0], cmdN[1]);
					}
					break;
				case 2:
					cout << "������㡢�յ��Ȩ�أ�Ĭ��Ȩ��Ϊ1��" << endl;
					cin >> cmd;
					cmdN = split(cmd);
					if (cmdN.size() == 2) {
						graph.addEdge(cmdN[0], cmdN[1], 1);
						lgraph.addEdge(cmdN[0], cmdN[1], 1);
					}
					else if (cmdN.size() == 1) {
						graph.addEdge(cmdN[0], cmdN[1], cmdN[2]);
						lgraph.addEdge(cmdN[0], cmdN[1], cmdN[2]);
					}
				case 0:
					quit = true;
					break;
				}
			}
			quit = false;
			break;
		case 2:
			tm = graph.AOV();
			for (unsigned x : tm) {
				cout << x << " ";
			}
			break;
		case 3:
			tm = graph.AOV();
			for (unsigned x : tm) {
				cout << x << " ";
			}
			break;
		case 4:
			cout << "���������յ�" << endl;
			cin >> cmd;
			cmdN = split(cmd);
			if (cmdN.size() == 2) {
				graph.Dijkstra(cmdN[0]);
			}
			break;
		case 5:
			quit = true;
			break;
		}
	}
}