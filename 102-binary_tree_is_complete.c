#include "binary_trees.h"

levelorder_queue_t *create_node(binary_tree_t *node);
void free_queue(levelorder_queue_t *head);
void push(binary_tree_t *node, levelorder_queue_t *head,
		levelorder_queue_t **tail);
void pop(levelorder_queue_t **head);
int binary_tree_is_complete(const binary_tree_t *tree);

/**
 * create_node - This will create
 * a new level order_queue_t node
 *
 * @node: Binary tree node for the new node
 *
 * Return: If an error (NULL) Else (Pointer to the new node)
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
 * free_queue - Func that frees a level order_queue_t queue
 *
 * @head: Pointer to head of the queue
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
 * push - This func will push a node to
 * the back of a level order_queue_t queue
 *
 * @node: Binary tree node to print and push
 *
 * @head: Double pointer to head of queue
 *
 * @tail: Double pointer to tail of queue
 *
 * Description: Upon malloc failure, exits (status code = 1)
 *
 */

void push(binary_tree_t *node, levelorder_queue_t *head,
		levelorder_queue_t **tail)
{
	levelorder_queue_t *new;

	new = create_node(node);
	if (new == NULL)
	{
		free_queue(head);
		exit(1);
	}
	(*tail)->next = new;
	*tail = new;
}

/**
 * pop - This will pop the head of a
 * level order_queue_t queue
 *
 * @head: Double pointer to head of queue
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
 * binary_tree_is_complete - This will only
 * check if a binary tree is complete
 *
 * @tree: Pointer to root node of the tree to traverse
 *
 * Return: If the tree is NULL or not complete (0) Else, (1)
 *
 * Description: Upon malloc failure, exit (status code = 1)
 *
 */

int binary_tree_is_complete(const binary_tree_t *tree)
{
	levelorder_queue_t *head, *tail;
	unsigned char myFlag = 0;

	if (tree == NULL)
		return (0);

	head = tail = create_node((binary_tree_t *)tree);
	if (head == NULL)
		exit(1);

	while (head != NULL)
	{
		if (head->node->left != NULL)
		{
			if (myFlag == 1)
			{
				free_queue(head);
				return (0);
			}
			push(head->node->left, head, &tail);
		}
		else
			myFlag = 1;
		if (head->node->right != NULL)
		{
			if (myFlag == 1)
			{
				free_queue(head);
				return (0);
			}
			push(head->node->right, head, &tail);
		}
		else
			myFlag = 1;
		pop(&head);
	}
	return (1);
}
