#include "binary_trees.h"

levelorder_queue_t *create_node(binary_tree_t *node);
void free_queue(levelorder_queue_t *head);
void pint_push(binary_tree_t *node, levelorder_queue_t *head,
		levelorder_queue_t **tail, void (*func)(int));
void pop(levelorder_queue_t **head);
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int));

/**
 * create_node - This func only creates
 * a new level order_queue_t node.
 *
 * @node: Binary tree node for the new node to contain.
 *
 * Return: If an error (NULL) Else, (Pointer to the new node)
 *
 */

levelorder_queue_t *create_node(binary_tree_t *node)
{
	levelorder_queue_t *new;

	new = malloc(sizeof(levelorder_queue_t));
	if (new == NULL)
		return (NULL);

	new->node = node;
	new->next = NULL;

	return (new);
}

/**
 * free_queue - Func that frees a level order_queue_t queue.
 *
 * @head: Pointer to head of queue
 *
 */

void free_queue(levelorder_queue_t *head)
{
	levelorder_queue_t *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

/**
 * pint_push - this will run a func on a given binary tree
 * node and push children into a level order_queue_t queue
 *
 * @node: Binary tree node to print and push
 *
 * @head: Double pointer to the head of the queue
 *
 * @tail: Double pointer to the tail of the queue
 *
 * @func: Pointer to the func to call on @node.
 *
 * Description: Upon malloc failure, exit (status code = 1)
 *
 */

void pint_push(binary_tree_t *node, levelorder_queue_t *head,
		levelorder_queue_t **tail, void (*func)(int))
{
	levelorder_queue_t *new;

	func(node->n);
	if (node->left != NULL)
	{
		new = create_node(node->left);
		if (new == NULL)
		{
			free_queue(head);
			exit(1);
		}
		(*tail)->next = new;
		*tail = new;
	}
	if (node->right != NULL)
	{
		new = create_node(node->right);
		if (new == NULL)
		{
			free_queue(head);
			exit(1);
		}
		(*tail)->next = new;
		*tail = new;
	}
}

/**
 * pop - This func pops the head of a level order_queue_t queue
 *
 * @head: Double pointer to head of the queue
 *
 */

void pop(levelorder_queue_t **head)
{
	levelorder_queue_t *tmp;

	tmp = (*head)->next;
	free(*head);
	*head = tmp;
}

/**
 * binary_tree_levelorder - This will traverse a
 * binary tree using alevel-order traversal
 *
 * @tree: Pointer to root node of the tree to traverse
 *
 * @func: Pointer to function to call for each node
 *
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	levelorder_queue_t *head, *tail;

	if (tree == NULL || func == NULL)
		return;

	head = tail = create_node((binary_tree_t *)tree);
	if (head == NULL)
		return;

	while (head != NULL)
	{
		pint_push(head->node, head, &tail, func);
		pop(&head);
	}
}
