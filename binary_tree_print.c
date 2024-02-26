#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h"

/* Original code from http://stackoverflow.com/a/13755911/5184480 */

/**
 * print_t - This Stores recursively each level in an array of strings
 *
 * @tree: The Pointer to the node to print
 *
 * @offset: Offset to print
 *
 * @depth: Depth of the node
 *
 * @s: A Buffer
 *
 * Return: length
 *
 */

static int print_t(const binary_tree_t *tree, int offset, int depth, char **s)
{
	char b[6];
	int width, left, right, is_left, eye;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(b, "(%03d)", tree->n);
	left = print_t(tree->left, offset, depth + 1, s);
	right = print_t(tree->right, offset + left + width, depth + 1, s);
	for (eye = 0; eye < width; eye++)
		s[depth][offset + left + eye] = b[eye];
	if (depth && is_left)
	{
		for (eye = 0; eye < width + right; eye++)
			s[depth - 1][offset + left + width / 2 + eye] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (eye = 0; eye < left + width; eye++)
			s[depth - 1][offset - width / 2 + eye] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	return (left + width + right);
}

/**
 * _height - This measures the height of a binary tree
 *
 * @tree: A pointer to the node to measures the height
 *
 * Return: The height of the tree starting at @node
 *
 */

static size_t _height(const binary_tree_t *tree)
{
	size_t height_l;
	size_t height_r;

	height_l = tree->left ? 1 + _height(tree->left) : 0;
	height_r = tree->right ? 1 + _height(tree->right) : 0;
	return (height_l > height_r ? height_l : height_r);
}

/**
 * binary_tree_print - This prints a binary tree
 *
 * @tree: A pointer to the root node of the tree to print
 *
 */

void binary_tree_print(const binary_tree_t *tree)
{
	char **s;
	size_t height, eye, jhay;

	if (!tree)
		return;
	height = _height(tree);
	s = malloc(sizeof(*s) * (height + 1));
	if (!s)
		return;
	for (eye = 0; eye < height + 1; eye++)
	{
		s[eye] = malloc(sizeof(**s) * 255);
		if (!s[eye])
			return;
		memset(s[eye], 32, 255);
	}
	print_t(tree, 0, 0, s);
	for (eye = 0; eye < height + 1; eye++)
	{
		for (jhay = 254; jhay > 1; --jhay)
		{
			if (s[eye][jhay] != ' ')
				break;
			s[eye][jhay] = '\0';
		}
		printf("%s\n", s[eye]);
		free(s[eye]);
	}
	free(s);
}
