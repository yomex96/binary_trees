#include "binary_trees.h"

/**
 * binary_trees_ancestor - Func that finds the
 * lowest common ancestor of two nodes.
 *
 * @first: Just a pointer to 1st node.
 *
 * @second: Just apointer to 2nd node.
 *
 * Return: If no common ancestors (NULL), else (common ancestor)
 *
 */

binary_tree_t *binary_trees_ancestor(const binary_tree_t *first,
		const binary_tree_t *second)
{
	binary_tree_t *mom, *pop;

	if (!first || !second)
		return (NULL);
	if (first == second)
		return ((binary_tree_t *)first);

	mom = first->parent, pop = second->parent;
	if (first == pop || !mom || (!mom->parent && pop))
		return (binary_trees_ancestor(first, pop));
	else if (mom == second || !pop || (!pop->parent && mom))
		return (binary_trees_ancestor(mom, second));
	return (binary_trees_ancestor(mom, pop));
}
