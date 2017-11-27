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
#include "split.h"
using namespace std;
struct ItemNode {
	int code : 24; // 24位保存编码
	int data : 8; // 8位保存一个char
	ItemNode(string s, char c) {
		code = 0;
		if (s.length() > 24)
			throw "Too long code string";
		for (char x : s) {
			code = code << 1;
			if (x == '1')
				code |= 0x01;
			else
				code &= (~0x01);
		}
		// cout << code << endl;
		data = c;
	}
	string toString() {
		char buf[25] = { 0 };
		int i = 0, c = 24;
		while ((code & (0x01 << c)) == 0)
			c--;
		while (c > -1) {
			buf[i++] = code & 0x01 << c ? '1' : '0';
			c--;
		}
		return string(buf);
	}
	int codeLength() {
		int c = 24;
		while ((code & (0x01 << c)) == 0)
			c--;
		return c;
	}
};

int getCodeLength(unsigned int code) {
	int c = 24;
	while ((code & (0x01 << c)) == 0 && c)
		c--;
	return c;
}

vector<ItemNode> makeHuffmanCode(ifstream &file) {
	vector<BiTree<unsigned>*> trees;
	unsigned int freq[128] = { 0 };
	vector<ItemNode> itemList;
	cout << "正在生成Huffman编码.." << endl;
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
	BiTree<unsigned> *t1, *t2, *t3;
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
	int listI = 0;
	unsigned bytes = 0;
	for (auto x : tab) {
		unsigned n = x.second;
		for (int i = 0; i < 128; i++) {
			if (freq[i] == n) {
				bytes += x.first.size() * freq[i];
				itemList.push_back(ItemNode(x.first, i));
				if (i != 10)
					printf("%-10d%-10c%-10d%-10s\n", i, i, n, x.first.c_str());
				else
					printf("%-10d%-10s%-10d%-10s\n", i, "\\n", n, x.first.c_str());
				freq[i] = 0;
				break;
			}
		}
	}
	cout << "压缩后大小" << bytes / 8 << "bytes.\n";
	return itemList;
}

//void huffman(string fname) {
//	if (fname.size() > 8 && fname.substr(fname.size() - 8).compare(".huffman") == 0) {
//		string codeFileName = fname + "code";
//		ifstream huffmanFile(fname, ios::binary);
//		ifstream huffmanCodeFile(codeFileName, ios::binary);
//		if (!huffmanFile.good()) {
//			cout << "打开文件失败" << endl;
//			return;
//		}
//		if (!huffmanCodeFile.good()) {
//			cout << "打开编码文件失败" << endl;
//			return;
//		}
//		BiTree<char> tree;
//		ItemNode *itemNode = new ItemNode("", 0);
//		while (!huffmanCodeFile.eof()) {
//			huffmanCodeFile.read((char*)itemNode, sizeof(ItemNode));
//			tree.addLeaves(itemNode->toString(), itemNode->data);
//		}
//		cout << "生成Huffman树" << endl;
//		vector<unsigned char> huffmanData;
//		char c;
//		while (!huffmanFile.eof()) {
//			huffmanFile.read(&c, sizeof(char));
//			huffmanData.push_back(c);
//		}
//		string result = tree.parseHuffman(&huffmanData[0], huffmanData.size());
//		cout << result;
//	}
//	else {
//		string compressedFileName = fname + ".huffman";
//		string codeFileName = fname + ".huffmancode";
//		ifstream f(fname);
//		ofstream codeFile(codeFileName);
//		ofstream huffmanFile(compressedFileName);
//		if (!f.good() || !codeFile.good() || !huffmanFile.good()) {
//			cout << "打开文件失败";
//			return;
//		}
//		vector<ItemNode> codeList = makeHuffmanCode(f);
//		for (auto it = codeList.begin(); it != codeList.end(); it++)
//			codeFile.write((char*)&(*it), sizeof(ItemNode));
//		codeFile.close();
//		f.close();
//		ifstream nf(fname);
//		cout << nf.tellg() << endl;
//		char c;
//		char buff[1024];
//		int codeBuff[128] = { 0 };
//		unsigned int countBits = 0, code, codeLength;
//		for (auto it = codeList.begin(); it != codeList.end(); it++)
//			codeBuff[(*it).data] = (*it).code;
//		while (!nf.eof()) {
//			c = nf.get();
//			code = codeBuff[c];
//			codeLength = getCodeLength(code);
//			if (countBits != 1024 * 8) {
//				for (int i = codeLength - 2; i >= 0; i--) {
//					buff[countBits / 8] |= ((code >> i) & 1) << countBits % 8;
//				}
//			}
//		}
//		huffmanFile.write(&buff[0], buff.size());
//		nf.close();
//		huffmanFile.close();
//		cout << "huffman编码完成" << endl;
//	}
//
//}
void testTree(void)
{
	// huffman("neu.txt");
	// huffman("neu.txt.huffman");
	bool quit = false;
	string cmd;
	vector<int> cmdN;
	string init = "AB/D//CE/F///", s;
	function<void(char)> f = [](char c) {cout << c << " "; };
	system("cls");
	while (!quit) {
		system("pause");
		system("cls");
		cout << "请选择操作\n1)测试二叉树\n2)Huffman编码\n0)返回上级菜单\n";
		cin >> cmd;
		cmdN = split(cmd);
		if (cmdN[0] == 1) {
			cout << "请按先序次序输入二叉树中结点的值，/表示值为空" << endl;
			cin >> s;
			if (s.size() == 0)
				s = init;
			BiTree<char> tree(s);
			cout << "按先序次序各节点的值：" << s << endl;
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
		}
		else if (cmdN[0] == 2) {
			ifstream file("neu.txt");
			makeHuffmanCode(file);
			file.close();
		}
		else
			quit = true;
	}
	
}