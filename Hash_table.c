#include "DHT.h"

int hash(char* value)
{
	int sum = 0;
	for (int i = 0; i < strlen(value); i++)
	{
		sum += (value[i] * i);
	}
	sum = sum % KEYSPACE;
	//printf("%d\n", sum);
	return sum;
}

void create_node_hash_table(Node *node, int key, char* value)
{
	Hash_table *hash_table = node->hash_table, *parent;
	
	while (hash_table != NULL) {
		parent = hash_table;
		hash_table = hash_table->next;
	}

	hash_table = malloc(sizeof(Hash_table));
	hash_table->key = key;
	hash_table->value = value;

	if (node->hash_table == NULL) {
		hash_table->next = NULL;
		hash_table->parent = NULL;
		node->hash_table = hash_table;
	} else {
		parent->next = hash_table;
		hash_table->parent = parent;
		hash_table->next = NULL;
	}
}

void add_value(List_node *list_node, char *value)
{
	int key = hash(value);
	//printf("%d\n", key);

	Node* node = search_key_in_node(list_node, key, 1);
	if (node == NULL) {
		printf("Error\n");
		return;
	}
	create_node_hash_table(node, key, value);
	create_node_hash_table(node->left, key, value);
}

Hash_table* search_key_in_table(Node* node, int key)
{
	Hash_table* hash_table = node->hash_table;
	while (hash_table != NULL && hash_table->key != key) {
		hash_table = hash_table->next;
	}
	return hash_table;
}

void free_hash_table(Hash_table* hash_table)
{
	hash_table->next = NULL;
	hash_table->parent = NULL;
	free(hash_table);
}