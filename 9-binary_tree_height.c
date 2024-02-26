#include "binary_trees.h"

/**
 * binary_tree_height - This is to measure the height of a binary tree.
 *
 * @tree: Pointer to the root node of the tree to measure the height.
 *
 * Return: If tree is NULL(0) else(height)
 *
 */

size_t binary_tree_height(const binary_tree_t *tree)
{
	if (tree)
	{
		size_t jhay = 0, eye = 0;

		jhay = tree->left ? 1 + binary_tree_height(tree->left) : 0;
		eye = tree->right ? 1 + binary_tree_height(tree->right) : 0;
		return ((jhay > eye) ? jhay : eye);
	}
	return (0);
}
