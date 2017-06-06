#include "yadisk/ops/subtract.hpp"

bool SHA256(const json& left, const json& right) {
	return left["sha256"] == right["sha256"];
}

bool MD5(const json& left, const json& right) {
	return left["md5"] == right["md5"];
}

auto Operations::subtract(Tree tree1, Tree tree2, Predicate pred) -> Tree&
{
	json flat_tree1 = tree1.flat_list();
	json flat_tree2 = tree2.flat_list();

	Tree* subtree = new Tree(tree1);

	for (int32_t i = 0; i < flat_tree1.size(); i++)
		for (int32_t j = 0; j < flat_tree2.size(); j++)
			if (flat_tree1[i]["path"] == flat_tree2[j]["path"] && pred(flat_tree1[i], flat_tree2[j])) {
				subtree->remove_file(flat_tree1[i]);
				flat_tree1.erase(i);
				flat_tree2.erase(j);
				if (i != 0) i--;
				j--;
			}

	return *subtree;
}
