#include "DHT.h"

List_node *create_list_node(int number)
{
	int border = 0, space;

	List_node *list_node = malloc(sizeof(List_node));
	if (list_node == NULL)
		return NULL;

	for (int i = 0; i < number; i++)
	{
		if (border == 0)
			border = ((KEYSPACE / number) / 2);
		space = (KEYSPACE / number) * i;
		create_node(list_node, space, border);
	}
	list_node->number_node = number;

	return list_node;
}

void change_first_node(List_node* list_node, Node* node)
{
	list_node->first_node = node;
}

void info_first_node(List_node* list_node)
{
	Node* node = list_node->first_node;

	printf("\n///First node///\n");
	printf("Id %d\t", node->id);

	if (node->hash_table != NULL) {
		printf("\nHash_table\n");
		Hash_table *hash_table = node->hash_table;
		while (hash_table != NULL) {
			printf("%d\t%s\n", hash_table->key, hash_table->value);
			hash_table = hash_table->next;
		}
	}
	printf("\n");
}

void search_value(List_node* list_node, char* value)
{
	int key = hash(value);
	Node *node = search_key_in_node(list_node, key, 2);
	if (node == NULL) {
		printf("Value not found\n");
		return;
	}
	printf("\n///Search value///\nNode: %p\nId: %d\n", node, node->id);
}

void delete_dht(List_node* list_node)
{
	Node* node = list_node->first_node;
	list_node->first_node = node->right;

	while (node != NULL) {
		free_node(node);
		node = list_node->first_node;
		if (node != NULL)
			list_node->first_node = node->right;
	}
	list_node = NULL;
}

void delete_node(List_node* list_node, int num)
{
	Node *node = list_node->first_node, *left = NULL;
	for (int i = 0; i < num; i++)
	{
		node = node->right;
	}

	if (node == list_node->first_node) {
		change_first_node(list_node, list_node->first_node->right);
	}

	left = node->left;
	free_node(node);
	list_node->number_node--;

	node = left->right;
	Hash_table* hash_table = node->hash_table;
	while (hash_table != NULL) {
		int node_id = node->id;
		int right_node_id = node->right->id;

		if (node_id > right_node_id)
			right_node_id = KEYSPACE;

		if (node_id <= hash_table->key && right_node_id > hash_table->key) {
			create_node_hash_table(left, hash_table->key, hash_table->value);
		}

		hash_table = hash_table->next;
	}
}

void add_node(List_node* list_node)
{
	Node *node = list_node->first_node, *first = node->right;
	int space, space_next;
	int node_id_next, right_node_id_next;
	int node_id = node->id;
	int right_node_id = node->right->id;

	if (node_id > right_node_id)
		right_node_id = KEYSPACE;

	space = right_node_id - node_id;

	for (int i = 0; i < list_node->number_node; i++)
	{
		node_id_next = node->right->id;
		right_node_id_next = node->right->right->id;

		if (node_id_next > right_node_id_next)
			right_node_id_next = KEYSPACE;

		space_next = right_node_id_next - node_id_next;

		if (space < space_next) {
			space = space_next;
			first = node->right;
		}
		node = node->right;
	}

	change_first_node(list_node, first);
	create_node(list_node, space / 2, space);

	node = first->left->left;
	Hash_table* hash_table = node->hash_table;
	while (hash_table != NULL) {
		node_id = node->id;
		right_node_id = node->right->id;

		node_id_next = node->right->id;
		right_node_id_next = node->right->right->id;

		if (node_id > right_node_id)
			right_node_id = KEYSPACE;

		if (node_id_next > right_node_id_next)
			right_node_id = KEYSPACE;

		if (right_node_id <= hash_table->key) {
			create_node_hash_table(node->right, hash_table->key, hash_table->value);
			if (node->right->right->id <= hash_table->key)
				delete_nht(node, hash_table);
		}
		hash_table = hash_table->next;
	}

	list_node->number_node++;
}