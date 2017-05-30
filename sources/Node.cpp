#include <iostream>
#include <string> 
#include "Tree.h"

class Node {

public:
	Tree * tree;
	Node * next;
	Node * prev;

	Node(Tree * _tree) {
		tree = _tree;
		next = NULL;
		prev = NULL;
	}

	Node(Tree * _tree, Node * _prev) {
		tree = _tree;
		next = NULL;
		prev = _prev;
	}

	Node * get_next() {
		return next;
	}

	Node * add_node(Tree * _tree) {
		if (tree == NULL) {
			tree = _tree;
		}
		else {
			next = new Node(_tree, this);
		}
	}

	void delete_node(Tree * _tree) {
		do {
			if (_tree == tree) {
				(*(*this).prev).next = next;
				(*(*this).next).prev = prev;
				delete_nodes((*this).tree);
				delete this;
				break;
			}
		} while (get_next() != NULL);
	}

	void delete_nodes(Tree * _tree) {
		Node * node = (*_tree).childs;
		while ((*node).get_next() != NULL) {
			node = (*node).get_next();
			delete_nodes((*node).tree);
			delete node;
		}
		delete _tree;
	}

	Tree get_data(Node node) {
		return *node.tree;
	}

	void set_data(Tree * _tree) {
		tree = _tree;
	}

	bool equals(Node * node) {
		return (*(*node).tree).equals((*this).tree) && (next == NULL && (*node).next == NULL || (*(*node).next).equals((*this).next));
	}

};
