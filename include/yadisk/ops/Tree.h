#pragma once
#include "Node.h";

class Tree {
public:
	Node * childs;
	Tree * parent;
	std::string file_name;
	void change_name(std::string new_name);
	Tree add_child(std::string file_name);
	Node find_tree(Tree * another_tree, Node * node);
	void delete_tree_node();
	bool equals(Tree * another_tree)
};