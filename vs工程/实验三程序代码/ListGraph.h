#pragma once
#include "LinkedList.h"
#include "MatrixGraph.h"
class ListGraph {
private:
	struct Edge {
		unsigned toVertex;
		bool isDouble;
		unsigned weight;
		Edge(unsigned to, unsigned w = 1, bool dou = false) :
			toVertex(to), weight(w), isDouble(dou) {}
	};
	struct Vertex {
		LinkedList<Edge*> edgeList;
		unsigned weight;
		unsigned number;
		Vertex(unsigned num, unsigned w = 1) : number(num), weight(w) {}
	};
	LinkedList<Vertex*> vertexList;
	unsigned vertexNum = 0;
	unsigned edgeNum = 0;
public:
	void addVertex(unsigned num, unsigned w = 1);
	void addEdge(unsigned s, unsigned e, unsigned w = 1, bool dou = false);
	void addDoubleEdge(unsigned s, unsigned e, unsigned w = 1) {
		addEdge(s, e, w, true);
	}
	void removeVertex(unsigned n);
	void removeEdge(unsigned s, unsigned e);
	void print(void);
};

void ListGraph::addVertex(unsigned num, unsigned w) {
	if ( vertexList.find([&](Vertex* v) {return v->number == num; }) != vertexList.length())
		return;
	vertexList.insert(new Vertex(num, w));
	vertexNum += 1;
}

void ListGraph::addEdge(unsigned s, unsigned e, unsigned w, bool dou) {
	if (vertexList.find([&](Vertex* v) {return v->number == s; }) == vertexList.length())
		addVertex(s);
	if (vertexList.find([&](Vertex* v) {return v->number == e; }) == vertexList.length())
		addVertex(e);
	Vertex* sNode = vertexList[vertexList.find([&](Vertex* v) {return v->number == s; })];
	sNode->edgeList.insert(new Edge(e, w, dou));
	edgeNum += 1;
}

inline void ListGraph::removeVertex(unsigned n) {
	unsigned p = vertexList.find([&](Vertex* a) {return a->number == n; });
	edgeNum -= vertexList.at(p)->edgeList.length();
	vertexList.remove(p);
	vertexNum -= 1;
}

inline void ListGraph::removeEdge(unsigned s, unsigned e)
{
	unsigned p = vertexList.find([&](Vertex* a) {return a->number == s; });
	unsigned ep = vertexList.at(p)->edgeList.find([&](Edge* a) {return a->toVertex == e; });
	vertexList.at(p)->edgeList.remove(ep);
	edgeNum -= 1;
}

void ListGraph::print(void) {
	using namespace std;
	cout << "邻接表，共有" << vertexNum << "个节点，" << edgeNum << "条边" << endl;
	for (unsigned i = 0; i < vertexList.length(); i++) {
		Vertex* n = vertexList.at(i);
		if (n->edgeList.length() != 0)
			cout << "顶点" << n->number << "的度为" << n->edgeList.length() << " 权重为" << n->weight << endl;
	}
	for (unsigned i = 0; i < vertexList.length(); i++) {
		Vertex* n = vertexList.at(i);
		for (unsigned j = 0; j < n->edgeList.length(); j++) {
			Edge* e = n->edgeList.at(j);
			if (e->isDouble)
				cout << "有向边" << n->number << " ----- " << e->toVertex << endl;
			else 
				cout << "无向边" << n->number << " ----> " << e->toVertex << endl;
		}
	}
}
