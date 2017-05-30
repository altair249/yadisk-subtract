#pragma once
#include "Tree.h";

class Node {
public:
	Tree * tree;
	Node * next;
	Node * prev;
	Node(Tree * tree);
	Node(Tree * _tree, Node * _prev);
	Node * get_next();
	Tree get_data(Node node);
	void set_data(Tree * _tree);
	Node add_node(Tree * _tree);
	void delete_node(Tree * _tree);
	bool equals(Node * node);
};