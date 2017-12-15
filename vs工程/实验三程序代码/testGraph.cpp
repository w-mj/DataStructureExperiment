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
	Stack<unsigned> reversePath;
	unsigned temp;
	int length;
	/*
	测试Dijkstra
	graph.addDoubleEdge(1, 3, 9);
	graph.addDoubleEdge(1, 2, 7);
	graph.addDoubleEdge(1, 6, 14);
	graph.addDoubleEdge(2, 3, 10);
	graph.addDoubleEdge(3, 6, 2);
	graph.addDoubleEdge(6, 5, 9);
	graph.addDoubleEdge(3, 4, 11);
	graph.addDoubleEdge(2, 4, 15);
	graph.addDoubleEdge(4, 5, 6);*/
	/*
	测试AOE
	graph.addEdge(1, 2, 3);
	graph.addEdge(1, 3, 2);
	graph.addEdge(2, 4, 2);
	graph.addEdge(3, 4, 4);
	graph.addEdge(3, 6, 3);
	graph.addEdge(4, 6, 2);
	graph.addEdge(2, 5, 3);
	graph.addEdge(5, 6, 1);*/
	/*
	测试AOV
	graph.addEdge(1, 4);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(1, 12);
	graph.addEdge(9, 12);
	graph.addEdge(9, 10);
	graph.addEdge(10, 12);
	graph.addEdge(9, 11);
	graph.addEdge(4, 5);
	graph.addEdge(2, 3);
	graph.addEdge(11, 6);
	graph.addEdge(3, 5);
	graph.addEdge(3, 7);
	graph.addEdge(3, 8);
	graph.addEdge(6, 8);
	graph.addEdge(5, 7);*/
	system("cls");
	while (!quit) {
		graph.print();
		cout << "请输入操作\n1)创建一个图\n2)计算AOV排序\n3)计算AOE关键路径\n4)求Dijkstra最短路径\n0)返回上级菜单\n";
		getline(cin, cmd);
		cmdN = split(cmd);
		// system("cls");
		switch (cmdN[0]) {
		case 1:
			while (!quit) {
				cout << "1)添加点\n2)添加边（如果边相关的点不存在会自动创建）\n0)返回上级\n";
				getline(cin, cmd);
				cmdN = split(cmd);
				switch (cmdN[0]) {
				case 1:
					cout << "输入点和权重（默认权重为1）" << endl;
					getline(cin, cmd);
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
					getline(cin, cmd);
					cmdN = split(cmd);
					if (cmdN.size() == 2) {
						graph.addEdge(cmdN[0], cmdN[1], 1);
						lgraph.addEdge(cmdN[0], cmdN[1], 1);
					}
					else if (cmdN.size() == 3) {
						graph.addEdge(cmdN[0], cmdN[1], cmdN[2]);
						lgraph.addEdge(cmdN[0], cmdN[1], cmdN[2]);
					}
					break;
				case 0:
					quit = true;
					break;
				}
			}
			quit = false;
			graph.print();
			system("pause");
			break;
		case 2:
			tm = graph.AOV();
			for (unsigned x : tm) {
				cout << x << " ";
			}	
			system("pause");
			break;
		case 3:
			tm = graph.AOE();
			cout << "AOE关键节点: ";
			for (unsigned x : tm) {
				cout << x << " ";
			}
			system("pause");
			break;
		case 4:
			cout << "输入起点和终点" << endl;
			getline(cin, cmd);
			cmdN = split(cmd);
			if (cmdN.size() == 2) {
				tm = graph.Dijkstra(cmdN[0], cmdN[1], length);
				cout << "最短路径为 ";
				for (temp = cmdN[1]; temp != cmdN[0]; temp = tm[temp])
					reversePath.push(temp);
				reversePath.push(cmdN[0]);
				while (!reversePath.empty())
					cout << reversePath.pop() << " ";
				cout << "\n长度为:" << length << endl;
			}
			system("pause");
			break;
		case 0:
			quit = true;
			break;
		}
	}
}