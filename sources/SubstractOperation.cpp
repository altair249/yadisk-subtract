#include <iostream>
#include <string> 
#include "Tree.h"

namespace Operations {
	Tree subtract(Tree * tree1, Tree * tree2) {
		Node * found_trees = (*tree2).find_tree(tree1, NULL);
		while ((*found_trees).get_next() != NULL) {
			if ((*(*found_trees).tree).equals(tree1)) {
				(*(*found_trees).tree).delete_tree_node();
				break;
			}
			found_trees = (*found_trees).next;
		}
	}
}
