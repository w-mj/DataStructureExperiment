#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "LinearList.h"
#include "ListGraph.h"
#include "Stack.h"
#include "Queue.h"
#define MAX_VERTEX_NUM 100
class MatrixGraph { // 邻接矩阵图
private:
	unsigned vertexWeight[MAX_VERTEX_NUM] = { 0 };  // 点权
	unsigned edgeWeight[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };  // 边权
	unsigned vertexNum = 0;  // 点数目
	unsigned edgeNum = 0;  // 边数目
public:

	MatrixGraph(const MatrixGraph& a);  // 复制构造函数
	MatrixGraph() = default;  // 默认构造函数
	void addVertex(unsigned n, unsigned weight = 1);  // 添加点
	void addEdge(unsigned s, unsigned e, unsigned weight = 1);  // 添加边
	void addDoubleEdge(unsigned s, unsigned e, unsigned weight = 1);  // 添加双向边
	std::vector<unsigned> AOV() const;  // AOV排序
	std::vector<unsigned> AOE() const;  // AOE路径
	std::vector<unsigned> getDegree();  // 获得每一个节点的度
	bool findPathDFS(unsigned s, unsigned e);  // 利用DFS判断s和e之间是否存在通路
	bool findPathBFS(unsigned s, unsigned e);  // 利用BFS判断s和e之间是否存在通路
	std::vector<unsigned> Dijkstra(unsigned s, unsigned e, int &length);  // Dijkstra求s和e之间的最短路径
	void print(void);  // 打印
};

inline MatrixGraph::MatrixGraph(const MatrixGraph & a) {
	memmove(vertexWeight, a.vertexWeight, sizeof(unsigned) * MAX_VERTEX_NUM);
	memmove(edgeWeight, a.edgeWeight, sizeof(unsigned) * MAX_VERTEX_NUM * MAX_VERTEX_NUM);
	vertexNum = a.vertexNum;
	edgeNum = a.edgeNum;
}

void MatrixGraph::addVertex(unsigned n, unsigned weight) {
	if (n < 0 || n > MAX_VERTEX_NUM)
		throw "Out of range";
	vertexWeight[n] = weight;
	vertexNum += 1;
}

void MatrixGraph::addEdge(unsigned s, unsigned e, unsigned weight) {
	if (s < 0  || s >= MAX_VERTEX_NUM || e < 0 || e >= MAX_VERTEX_NUM )
		throw "Out of range";
	if (vertexWeight[s] == 0)
		addVertex(s);
	if (vertexWeight[e] == 0)
		addVertex(e);
	edgeWeight[s][e] = weight;
	edgeNum += 1;
}

void MatrixGraph::addDoubleEdge(unsigned s, unsigned e, unsigned weight) {
	addEdge(s, e, weight);
	addEdge(e, s, weight);
	edgeNum -= 1;
}

inline std::vector<unsigned> MatrixGraph::AOV() const
{
	using namespace std;
	std::vector<unsigned> result;
	MatrixGraph g(*this);
	bool head = false;
	while (result.size() != vertexNum) {
		for (unsigned i = 0; i < MAX_VERTEX_NUM; i++) {
			if (g.vertexWeight[i] == 0)
				continue;
			head = true;
			for (int j = 0; j < MAX_VERTEX_NUM; j++) {
				if (g.edgeWeight[j][i] != 0) {
					head = false;
					break;
				}
			}
			if (head) {
				result.push_back(i);
				for (int j = 0; j < MAX_VERTEX_NUM; j++)
					g.edgeWeight[i][j] = 0;
				g.vertexWeight[i] = 0;
				i = 0;
			}
		}
	}
	return result;
}

inline std::vector<unsigned> MatrixGraph::AOE() const
{
	using namespace std;
	vector<unsigned> result, aov = AOV();
	unsigned s = aov.front(), e = aov.back();
	unsigned ve[MAX_VERTEX_NUM] = { 0 }, vl[MAX_VERTEX_NUM] = { 0 };
	for (int j = 0; j < MAX_VERTEX_NUM; j++) {
		if (vertexWeight[j] == 0) continue;
		unsigned maxs = 0;
		for (vector<unsigned>::iterator i = aov.begin(); i != aov.end(); i++) {
			if (edgeWeight[*i][j] != 0)
				maxs = max(maxs, ve[*i] + edgeWeight[*i][j]);
		}
		vl[j] = ve[j] = maxs;
	}

	for (int i = MAX_VERTEX_NUM - 1; i >= 0; i--) {
		if (i == e || vertexWeight[i] == 0) continue;
		unsigned mins = ve[e];
		for (vector<unsigned>::reverse_iterator j = aov.rbegin(); j != aov.rend(); j++) {
			if (edgeWeight[i][*j] != 0)
				mins = min(mins, vl[*j] - edgeWeight[i][*j]);
		}
		vl[i] = mins;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (vertexWeight[i] != 0 && vl[i] == ve[i])
			result.push_back(i);
	}
	return result;

}


std::vector<unsigned> MatrixGraph::getDegree() {
	std::vector<unsigned> result(MAX_VERTEX_NUM);
	for (unsigned i = 0; i < MAX_VERTEX_NUM; i++) {
		unsigned w = 0;
		for (unsigned j = 0; j < MAX_VERTEX_NUM; j++) {
			if (edgeWeight[i][j] != 0)
				w += 1;
		}
		result[i] = w;
	}
	return result;
}

inline bool MatrixGraph::findPathDFS(unsigned s, unsigned e)
{
	bool visited[MAX_VERTEX_NUM] = { 0 };
	Stack<unsigned> stack;
	stack.push(s);
	while (!stack.empty()) {
		unsigned now = stack.pop();
		if (visited[now])
			continue;
		visited[now] = true;
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			if (edgeWeight[now][j] != 0) {
				if (j == e)
					return true;
				stack.push(edgeWeight[now][j]);
			}
		}
	}
	return false;
}

inline bool MatrixGraph::findPathBFS(unsigned s, unsigned e)
{
	bool visited[MAX_VERTEX_NUM] = { 0 };
	Queue<unsigned> queue;
	queue.push(s);
	while (!queue.empty()) {
		unsigned now = queue.pop();
		if (visited[now])
			continue;
		visited[now] = true;
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			if (edgeWeight[now][j] != 0) {
				if (j == e)
					return true;
				queue.push(edgeWeight[now][j]);
			}
		}
	}
	return false;
}

std::vector<unsigned> MatrixGraph::Dijkstra(unsigned s, unsigned e, int &ll)
{
	using namespace std;
	vector<unsigned> result;
	result.resize(MAX_VERTEX_NUM);
	unsigned length[MAX_VERTEX_NUM] = { 0 };
	unsigned pre[MAX_VERTEX_NUM] = { 0 };
	bool visited[MAX_VERTEX_NUM] = { 0 };
	LinearList<unsigned> list;
	list.insert(s);
	while (!list.empty()) {
		unsigned nowP = 0;
		for (unsigned i = 0; i < list.length(); i++) {
			if (length[list.at(i)] < length[list.at(nowP)])
				nowP = i;
		}
		unsigned now = list.at(nowP);
		list.remove(nowP);
		if (visited[now]) continue;
		visited[now] = true;
		for (unsigned j = 0; j < MAX_VERTEX_NUM; j++) {
			if (vertexWeight[j] == 0 || edgeWeight[now][j] == 0)
				continue;
			if (length[j] == 0 || length[j] > length[now] + edgeWeight[now][j]) {
				length[j] = length[now] + edgeWeight[now][j];
				pre[j] = now;
			}
			list.insert(j);
		}
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (length[i] != 0 || i == s) {
			// std::cout << i << "  " << pre[i] << "  " << length[i] << std::endl;
			result[i] = pre[i];
		}
	}
	ll = length[e];
	return result;
}

void MatrixGraph::print(void) {
	using namespace std;
	vector<unsigned> degree = getDegree();
	cout << "图共有" << vertexNum << "个顶点，" << edgeNum << "条边" << endl;
	for (unsigned i = 0; i < MAX_VERTEX_NUM; i++) {
		if (degree[i] != 0)
			cout << "顶点" << i << "的度为" << degree[i] << "  权重为" << vertexWeight[i] << endl;
	}
	for (unsigned i = 0; i < MAX_VERTEX_NUM; i++) {
		for (unsigned j = 0; j < MAX_VERTEX_NUM; j++) {
			if (edgeWeight[i][j] != 0)
				if (i <= j && edgeWeight[i][j] == edgeWeight[j][i])
					cout << "无向边" << i << " ----- " << j << "  权重为" << edgeWeight[i][j] << endl;
				else if (i > j && edgeWeight[i][j] == edgeWeight[j][i])
					continue;
				else
					cout << "有向边" << i << " ----> " << j << "  权重为" << edgeWeight[i][j] << endl;
		}
	}
}
