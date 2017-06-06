#ifndef TREE_RESOURCE_HPP
#define TREE_RESOURCE_HPP

#include "yadisk/ops/Resource.hpp"
using yadisk::ops::Resource;

namespace yadisk
{
	namespace ops
	{
		struct Node
		{
			Resource* data;
			Node* parent;
			Node* brothers;
			Node* childs;
		};

		class Tree
		{
		public:

			Node* root;

			Tree() { root = NULL; }

			Tree(Tree& input);

			auto add_child(const Resource& data, Node* parent = NULL) -> Node*;

			auto operator=(const Tree& input) -> Tree&;

			auto flat_list() -> json&;

			auto remove_file(const json& data) -> void;

			~Tree();

		protected:

			auto recursive_files(Node* node, json* files) -> void;

			auto recursive_remove(Node* node, const json& data) -> void;

			auto recursive_copy(Node* node, Node* parent = NULL) -> Node*;

			auto recursive_del(Node* node) -> void;
		};
	}
}


#endif
