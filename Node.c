#include "DHT.h"

void create_node(List_node *list_node, int space, int border)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL)
		return;

	node->right = node;
	node->left = node;
	node->id = space;
	node->border = border;
	node->hash_table = NULL;

	if (list_node->first_node == NULL) {
		list_node->first_node = node;
	} else {
		add_node_to_list(list_node->first_node, node);
	}
}

void add_node_to_list(Node *first_node, Node* node)
{
	if (first_node != NULL) {
		first_node->left->right = node;
		node->left = first_node->left;
		first_node->left = node;
		node->right = first_node;
	}
}

Node* search_key_in_node(List_node *list_node, int key, int act)
{
	Node *node = list_node->first_node;
	int node_id, right_node_id;

	for (int i = 0; i < list_node->number_node; i++)
	{
		node_id = node->id;
		right_node_id = node->right->id;
		if (right_node_id == 0)
			right_node_id = KEYSPACE;

		if (node_id <= key && right_node_id > key) {
			if (search_key_in_table(node, key) == NULL) {
				return node;
			} else if (act == 1) {
				printf("Key already exists\n");
				return NULL;
			} else if (act == 2) {
				return node;
			}
		}
		node = node->right;
	}
	return NULL;
}

void free_node(Node *node)
{
	Hash_table* hash_table = node->hash_table;

	if (node->right != NULL)
		node->right->left = node->left;
	if (node->left != NULL) 
		node->left->right = node->right;

	node->right = NULL;
	node->left = NULL;

	if (hash_table != NULL)
		node->hash_table = hash_table->next;

	if (node->hash_table != NULL)
		node->hash_table->parent = NULL;

	while (hash_table != NULL) {
		free_hash_table(hash_table);

		hash_table = node->hash_table;

		if (hash_table != NULL)
			node->hash_table = hash_table->next;

		if (node->hash_table != NULL)
			node->hash_table->parent = NULL;
	}
}