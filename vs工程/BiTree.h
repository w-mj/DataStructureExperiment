#pragma once
#include <string>
#include "Stack.h"
#include <functional>
#include <algorithm>
template<class T> // 泛型
class BiTree {
private:
	struct BiTreeNode { // 使用二叉链表实现二叉树
		BiTreeNode *left, *right;   // 二叉链表的左右指针
		T data;  // 数据节点
		BiTreeNode(T d) : data(d), left(nullptr), right(nullptr) {}  // 构造一个二叉链表的节点
		BiTreeNode(const BiTreeNode& n1, const BiTreeNode& n2);  // 利用两个节点，生成他们的父节点（用于Huffman）
		BiTreeNode(const BiTreeNode& another);  // 复制构造函数
		~BiTreeNode();  // 析构函数
		unsigned height(void);  // 树高的递归函数体
		void postOrder(std::function<void(T)> f);  // 后序遍历的递归函数体
		vector<pair<string, unsigned>> huffman(string last);  // Huffman编码的递归函数体
	};
	BiTreeNode* tree;  // 树本体
	unsigned int height;  // 树高
	unsigned int numOfNodes;  // 节点数目
public:
	BiTree() : tree(nullptr), height(0), numOfNodes(0) {}  // 构造函数，生成空树
	BiTree(std::string preOrder);  // 按照先序遍历生成二叉树
	BiTree(const BiTree& another); // 复制构造函数
	BiTree(const T& a) : tree(new BiTreeNode(a)), height(1), numOfNodes(1) {}  // 生成只有一个元素的树
	BiTree(const BiTree<T>& t1, const BiTree<T>& t2);  // 利用两个节点，生成他们的父节点（用于Huffman
	~BiTree(); // 析构函数
	void preOrder(std::function<void(T)> f);  // 前序遍历，按照前序顺序对每一个元素调用f函数
	void inOrder(std::function<void(T)> f);  // 中序遍历
	void postOrder(std::function<void(T)> f);  // 后序遍历
	void lavelOrder(std::function<void(T)> f);  // 层次遍历
	T rootNode(void) { return tree->data; }  // 返回树根节点的值
	unsigned getHeight(void) { return tree -> height(); }  // 获得树高
	unsigned getNumOfNodes(void) { return numOfNodes; }  // 获得节点数数量
	BiTree<T> operator=(const BiTree<T>& another);  // 重载=号，作用与复制构造函数类似
	void addLeaves(std::string s, T d);  // 按照字符串添加树叶（用于Huffman解码）
	string parseHuffman(unsigned char* binList, unsigned lenght);
	vector < pair < string, unsigned>> huffmanOrder(void);  // 返回树的Huffman编码
};

template<class T>
inline BiTree<T>::BiTree(std::string preOrder) {
	Stack<BiTreeNode*> stack;
	if (preOrder.size() == 0)
		return;
	tree = new BiTreeNode(preOrder[0]);
	stack.push(tree);
	for (std::string::iterator it = preOrder.begin() + 1;
		it != preOrder.end() && !stack.empty();) {
		while (it != preOrder.end() && *it != '/') {
			stack.top()->left = new BiTreeNode(*it);
			numOfNodes += 1;
			stack.push(stack.top()->left);
			it++;
		}
		it++;
		while (it != preOrder.end() && *it == '/' && !stack.empty()) {
			stack.pop();
			it++;
		}
		if (it != preOrder.end() && !stack.empty()) {
			stack.top()->right = new BiTreeNode(*it++);
			numOfNodes += 1;
			stack.push(stack.pop()->right);
		}
	}
}

template<class T>
inline BiTree<T>::BiTree(const BiTree & another)
{
	height = another.height;
	numOfNodes = another.numOfNodes;
	tree = new BiTreeNode(another.tree);
}

template<class T>
inline BiTree<T>::BiTree(const BiTree<T>& t1, const BiTree<T>& t2)
{
	tree = new BiTreeNode(*t1.tree, *t2.tree);
	height = t1.height + t2.height;
}

template<class T>
inline BiTree<T>::~BiTree()
{
	delete tree;
}

template<class T>
inline void BiTree<T>::preOrder(std::function<void(T)> f)
{
	Stack<BiTreeNode*> stack;
	BiTreeNode* t = tree;
	while (t != nullptr || !stack.empty()) {
		while (t != nullptr) {
			f(t -> data);
			stack.push(t);
			t = t->left;
		}
		if (!stack.empty()) {
			t = stack.pop()->right;
		}
	}
}

template<class T>
inline void BiTree<T>::inOrder(std::function<void(T)> f)
{
	Stack<BiTreeNode*> stack;
	BiTreeNode* t = tree;
	while (t != nullptr || !stack.empty()) {
		while (t != nullptr) {
			stack.push(t);
			t = t->left;
		}
		if (!stack.empty()) {
			t = stack.pop();
			f(t -> data);
			t = t->right;
		}
	}
}

template<class T>
inline void BiTree<T>::postOrder(std::function<void(T)> f)
{
	tree->postOrder(f);
}

template<class T>
inline void BiTree<T>::lavelOrder(std::function<void(T)> f)
{
	Queue<BiTreeNode* > q;
	q.push(tree);
	while (!q.empty()) {
		int n = q.size();
		for (int i = 0; i < n; i++) {
			BiTreeNode* x = q.pop();
			f(x->data);
			if (x->left != nullptr)
				q.push(x->left);
			if (x->right != nullptr)
				q.push(x->right);
		}
	}
}

template<class T>
inline BiTree<T> BiTree<T>::operator=(const BiTree<T>& another)
{
	return BiTree<T>(another);
}

template<class T>
inline void BiTree<T>::addLeaves(std::string s, T c) {
	BiTreeNode* cursor = tree;
	if (cursor == nullptr)
		cursor = new BiTreeNode(-1);
	for (char x : s) {
		if (x == '0') {
			if (cursor->left == nullptr)
				cursor->left = new BiTreeNode(-1);
			cursor = cursor->left;
		}
		else {
			if (x == '1') {
				if (cursor->right == nullptr)
					cursor->right = new BiTreeNode(-1);
				cursor = cursor->right;
			}
		}
		cursor->data = c;
	}
}

template<class T>
inline string BiTree<T>::parseHuffman(unsigned char * binList, unsigned length)
{
	using namespace std;
	string ss;
	unsigned char byte, offset;
	BiTreeNode* cursor = tree;
	for (int i = 0; i < length; i++) {
		byte = *(binList + (i / 8) * sizeof(unsigned char));
		offset = i % 8;
		if (cursor->left == nullptr && cursor->right == nullptr) {
			ss += cursor->data;
			cursor = tree;
		}
		else {
			if (byte << (0x80 >> offset) != 0) {
				if (cursor->left == nullptr && cursor->right != nullptr)
					throw "try to reach null";
				cursor = cursor->left;
			}
			else {
				if (cursor->right == nullptr && cursor->left != nullptr)
					throw "try to reach null";
				cursor = cursor->right;
			}
		}
	}
	return ss;
}

template<class T>
inline vector<pair<string, unsigned>> BiTree<T>::huffmanOrder(void)
{
	return tree->huffman("");
}


template<class T>
inline BiTree<T>::BiTreeNode::BiTreeNode(const BiTreeNode & n1, const BiTreeNode& n2)
{
	data = n1.data + n2.data;
	left = new BiTreeNode(n1);
	right = new BiTreeNode(n2);
}

template<class T>
inline BiTree<T>::BiTreeNode::BiTreeNode(const BiTreeNode & another)
{
	left = nullptr;
	right = nullptr;
	data = another.data;
	if (another.left != nullptr)
		left = new BiTreeNode(*another.left);
	if (another.right != nullptr)
		right = new BiTreeNode(*another.right);
}

template<class T>
inline BiTree<T>::BiTreeNode::~BiTreeNode()
{
	if (left != nullptr)
		delete left;
	if (right != nullptr)
		delete right;
}

template<class T>
inline unsigned BiTree<T>::BiTreeNode::height(void)
{
	return max(left == nullptr ? 0 : left->height(),
		right == nullptr ? 0 : right->height()) + 1;
}

template<class T>
inline void BiTree<T>::BiTreeNode::postOrder(std::function<void(T)> f)
{
	if (left != nullptr)
		left->postOrder(f);
	if (right != nullptr)
		right->postOrder(f);
	f(data);
}

template<class T>
inline vector<pair<string, unsigned>> BiTree<T>::BiTreeNode::huffman(string last)
{
	vector<pair<string, unsigned>> ret;
	if (left == nullptr && right == nullptr)
		ret.push_back(pair<string, unsigned>(last, data));
	else {
		if (left != nullptr) {
			vector<pair<string, unsigned>> an = left->huffman(last + "1");
			ret.insert(ret.end(), an.begin(), an.end());
		}
		if (right != nullptr) {
			vector<pair<string, unsigned>> an = right->huffman(last + "0");
			ret.insert(ret.end(), an.begin(), an.end());
		}
	}
	return ret;
}
