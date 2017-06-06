#include "yadisk/ops/Tree.hpp"

auto yadisk::ops::Tree::recursive_del(Node* node) -> void
{
	if (node != NULL) {
		recursive_del(node->brothers);
		recursive_del(node->childs);
		delete node->data;
		delete node;
	}
}

yadisk::ops::Tree::Tree(Tree& input)
{
	root = recursive_copy(input.root);
}

auto yadisk::ops::Tree::add_child(const Resource& data, Node* parent) -> Node*
{
	if (parent != NULL) {
		Node* child = new Node;
		child->data = new Resource(data);
		child->parent = parent;
		child->brothers = parent->childs;
		parent->childs = child;
		child->childs = NULL;
		return parent->childs;
	} else {
		recursive_del(root);
		root = new Node;
		root->data = new Resource(data);
		root->parent = NULL;
		root->brothers = NULL;
		root->childs = NULL;
		return root;
	}
}

auto yadisk::ops::Tree::operator=(const Tree& input) -> Tree&
{
	if (root != input.root) {
		recursive_del(root);
		root = recursive_copy(input.root);
	}
	return *this;
}

auto yadisk::ops::Tree::flat_list() -> json&
{
	json *list = new json();
	recursive_files(root, list);
	return *list;
}

auto yadisk::ops::Tree::remove_file(const json& data) -> void
{
	recursive_remove(root, data);
}

yadisk::ops::Tree::~Tree()
{
	recursive_del(root);
}

auto yadisk::ops::Tree::recursive_files(Node *node, json* files) -> void
{
	if (node != NULL) {

		for (int32_t i = 0; i < node->data->total(); i++)
			files->push_back(node->data->at(i));

		recursive_files(node->brothers, files);
		recursive_files(node->childs, files);
	}
}

auto yadisk::ops::Tree::recursive_remove(Node *node, const json& data) -> void
{
	if (node != NULL) {

		for (int32_t i = 0; i < node->data->total(); i++)
			if (node->data->at(i) == data) {
				node->data->erase(i);
				return;
			}

		recursive_remove(node->brothers, data);
		recursive_remove(node->childs, data);
	}
}

auto yadisk::ops::Tree::recursive_copy(Node* node, Node* parent) -> Node*
{
	if (node != NULL) {
		Node* dublicate = new Node;
		dublicate->data = new Resource(node->data);
		dublicate->parent = parent;
		dublicate->brothers = recursive_copy(node->brothers, parent);
		dublicate->childs = recursive_copy(node->childs, dublicate);
		return dublicate;
	} else
		return NULL;
}
