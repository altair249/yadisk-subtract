#include <iostream>
#include <string> 
#include "Node.h"

class Tree {

public:
	std::string file_name;
	Node * childs;
	Tree * parent;

	Tree() {

	}

	Tree(std::string name) {
		file_name = name;
		parent = NULL;
		childs = new Node(NULL);
	}

	void change_name(std::string new_name) {
		file_name = new_name;
	}

	Tree add_child(std::string file_name) {
		Tree * new_tree = new Tree(file_name);
		(*childs).add_node(new_tree);
	}

	void delete_tree_node() {
		Tree * parent = (*this).parent;
		if (parent != NULL) {
			(*(*parent).childs).delete_node(this);
		}
	}

	Node find_tree(Tree * another_tree, Node * smth) {
		if ((*this).file_name == (*another_tree).file_name) {
			if (smth == NULL) {
				smth = new Node(this);
			}
			else {
				Node * node = new Node(this, smth);
				(*smth).next = node;
			}
		}
		if (childs != NULL) {
			Node * node = childs;
			(*(*node).tree).find_tree(another_tree, smth);
			while ((*node).get_next() != NULL) {
				node = (*node).get_next();
				(*(*node).tree).find_tree(another_tree, smth);
			}
		}
	}

	bool equals(Tree * another_tree) {
		return
			((*another_tree).file_name == (*this).file_name) &&
			(childs == NULL && (*another_tree).childs == NULL ||
				(*childs).equals((*another_tree).childs));
	}
};
