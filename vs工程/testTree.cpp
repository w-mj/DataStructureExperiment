#include "BiTree.h"
#include "Stack.h"
#include "Queue.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <direct.h>  
#include <vector>
using namespace std;
void huffman(string fname) {
	vector<BiTree<unsigned>*> trees;
	unsigned int freq[128] = { 0 }; 
	ifstream file(fname);
	if (!file.is_open()) {
		cout << "Error opening file";
	}
	char c;
	while (!file.eof()) {
		c = file.get();
		if (c < 0 || c > 128)
			continue;
		freq[c] += 1;
	}
	for (int i = 0; i < 128; i++) {
		if (freq[i] != 0)
			trees.push_back(new BiTree<unsigned int>(freq[i]));
	}
	BiTree<unsigned> *t1,  *t2, *t3;
	while (trees.size() > 1) {
		sort(trees.begin(), trees.end(),
			[](BiTree<unsigned>* t1, BiTree<unsigned>* t2) {return t1->rootNode() < t2->rootNode(); });
		t1 = trees[0];
		t2 = trees[1];
		trees.erase(trees.begin());
		trees.erase(trees.begin());
		t3 = new BiTree<unsigned>(*t1, *t2);
		trees.push_back(t3);
		delete t1;
		delete t2;
	}
	vector<pair<string, unsigned>> tab = trees.front()->huffmanOrder();
	sort(tab.begin(), tab.end(),
		[](const pair<string, unsigned> a, const pair<string, unsigned> b) {return a.second > b.second; });
	for (auto x : tab) {
		unsigned n = x.second;
		for (int i = 0; i < 128; i++) {
			if (freq[i] == n) {
				if (i != 10)
					printf("%-10d%-10c%-10d%-10s\n", i, i, n, x.first.c_str());
				else
					printf("%-10d%-10s%-10d%-10s\n", i, "\\n", n, x.first.c_str());
				freq[i] = 0;
			}
		}
	}
	file.close();
}
void testTree(void)
{
	huffman("neu.txt");
	return;
	string init = "AB/D//CE/F///";
	BiTree<char> tree(init);
	function<void(char)> f = [](char c) {cout << c << " "; };
	cout << "按先序次序各节点的值：" << init << endl;
	cout << "树高为" << tree.getHeight() << "  共有" << tree.getNumOfNodes() << "个节点" << endl;
	cout << "先序遍历：";
	tree.preOrder(f);
	cout << endl;
	cout << "中序遍历：";
	tree.inOrder(f);
	cout << endl;
	cout << "后序遍历：";
	tree.postOrder(f);
	cout << endl;
	cout << "层次遍历：";
	tree.lavelOrder(f);
	cout << endl;
	cin >> init;
}