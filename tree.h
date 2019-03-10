#pragma once
#include <iostream>
#include <deque>
#include <utility>

class tree
{
private:	

	struct node
	{
		size_t nodeSize = 0;
		int lKey = 0;
		int rKey = 0;

		node* lNode = nullptr;
		node* mNode = nullptr;
		node* rNode = nullptr;		
	};

	size_t _size = 0;
	node* headNode;

	node* nodeInsert(node* nodeForInsert, int& value);
	node* splitLeaf(node* nodeForSplit, int& value);
	node* splitNode(node* nodeForSplit, node* joinNode, int& value);

	bool eraseNode(node * headNode, int value);
	bool distribNode(node *curNode, node* delNode);
	bool returnKeyFromLeaf(node* curNode, int &value);
	bool mergeNode(node* curNode, node* nextNode);

	bool isLeaf(node *curNode);
	bool isNodeWithLeaf(node *curNode);
	void sortNode(node *curNode);
	void swap(node *curNode);
	bool checkNode(node* curNode);
	
	node* findNode(node* curNode, int value);

	bool printLevel(size_t level, node *curNode);

public:
	tree();

	~tree() = default;
	
	size_t size();
	
	void insert(int value);
	void erase(int value);
	bool find(int value);

	void printTree();
	void printTree2();
	bool checkTree();
};

