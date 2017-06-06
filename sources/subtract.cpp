#include "yadisk/ops/subtract.hpp"

/**
Выполняет сравнение хэш-функций по алгоритму SHA-256
\param[in] json одного дерева
\param[in] json другого дерева
\return true, если хэши совпадают, false в противном случае
**/
bool SHA256(const json& left, const json& right) {
	return left["sha256"] == right["sha256"];
}

/**
Выполняет сравнение хэш-функций по алгоритму MD5
\param[in] json одного дерева
\param[in] json другого дерева
\return true, если хэши совпадают, false в противном случае
**/
bool MD5(const json& left, const json& right) {
	return left["md5"] == right["md5"];
}

/**
Выполняет вычитание двух деревьев
\param[in] первое дерево
\param[in] второе дерево
\param[in] предикат (true, если ресурсы совпадают; false в противном случае)
\return поддерево, являющееся результатом вычитания второго дерева из первого
**/
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
