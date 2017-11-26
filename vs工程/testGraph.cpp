#include "MatrixGraph.h"
#include "ListGraph.h"

void testGraph(void) {
	MatrixGraph graph;
	graph.addDoubleEdge(1, 6, 14);
	graph.addDoubleEdge(1, 3, 9);
	graph.addDoubleEdge(1, 2, 7);
	graph.addDoubleEdge(3, 6, 2);
	graph.addDoubleEdge(3, 2, 10);
	graph.addDoubleEdge(6, 5, 9);
	graph.addDoubleEdge(3, 4, 11);
	graph.addDoubleEdge(2, 4, 15);
	graph.addDoubleEdge(4, 5, 6);
	graph.print();
	graph.Dijkstra(1);
	/*graph.addEdge(1, 4);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(1, 12);
	graph.addEdge(4, 5);
	graph.addEdge(2, 3);
	graph.addEdge(9, 12);
	graph.addEdge(9, 10);
	graph.addEdge(9, 11);
	graph.addEdge(5, 7);
	graph.addEdge(3, 7);
	graph.addEdge(11, 6);
	graph.addEdge(3, 8);
	graph.addEdge(6, 8);*/
	/*graph.addEdge(1, 2, 6);
	graph.addEdge(1, 3, 4);
	graph.addEdge(1, 4, 5);
	graph.addEdge(2, 5, 1);
	graph.addEdge(3, 5, 1);
	graph.addEdge(4, 6, 2);
	graph.addEdge(5, 7, 9);
	graph.addEdge(5, 8, 7);
	graph.addEdge(6, 8, 4);
	graph.addEdge(7, 9, 2);
	graph.addEdge(8, 9, 4);*/
	/*graph.addEdge(1, 2, 3);
	graph.addEdge(1, 3, 2);
	graph.addEdge(2, 4, 2);
	graph.addEdge(3, 4, 4);
	graph.addEdge(2, 5, 3);
	graph.addEdge(5, 6, 1);
	graph.addEdge(4, 6, 2);
	graph.addEdge(3, 6, 3);*/
	/*graph.print();
	vector<unsigned> aov = graph.AOE();
	for (unsigned x : aov) {
		cout << x << " ";
	}*/
	cout << endl;
}