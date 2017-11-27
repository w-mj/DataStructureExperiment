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
		cout << "请输入操作\n1)创建一个图\n2)计算AOV排序\n3)计算AOE关键路径\n4)求Dijkstra最短路径\n0)返回上级菜单\n";
		cin >> cmd;
		cmdN = split(cmd);
		switch (cmdN[0]) {
		case 1:
			while (!quit) {
				cout << "1)添加点\n2)添加边（如果边相关的点不存在会自动创建）\n0)返回上级\n";
				cin >> cmd;
				cmdN = split(cmd);
				switch (cmdN[0]) {
				case 1:
					cout << "输入点和权重（默认权重为1）" << endl;
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
					cout << "输入起点、终点和权重（默认权重为1）" << endl;
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
			cout << "输入起点和终点" << endl;
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