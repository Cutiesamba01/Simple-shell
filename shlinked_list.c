#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: adr of the pointer to the head node
 * @s: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *s, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (s)
	{
		new_head->s = _strdup(s);
		if (!new_head->s)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @s: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *s, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (s)
	{
		new_node->s = _strdup(s);
		if (!new_node->s)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the s element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t r = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		r++;
	}
	return (r);
}

/**
 * delete_node_at_index - deletes node at a given index
 * @head: adr of pointer to first node
 * @in: index of node to be deleted
 *
 * Return: 1 if successful / 0 otherwise
 */

int delete_node_at_index(list_t **head, unsigned int in)
{
	list_t *node, *prev_node;
	unsigned int h = 0;

	if (!head || !*head)
		return (0);
	if (!in)
	{
		node = *head;
		*head = (*head)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (h == in)
		{
			prev_node->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		h++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all the nodes of a list
 * @head_ptr: adr of pointer to the head node
 *
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->s);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
