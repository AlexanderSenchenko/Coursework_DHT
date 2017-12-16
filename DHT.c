#include "DHT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYSPACE 999

//List_node
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


//Node
void create_node(List_node *list_node, int space, int border)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL)
		return;

	node->right = node;
	node->left = node;
	node->id = space;
	node->border = border;

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

Node* search_key_in_node(List_node *list_node, int key)
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
			} else {
				printf("Ключ уже есть\n");
				return NULL;
			}
		}
		node = node->right;
	}
	return NULL;
}

Hash_table* search_key_in_table(Node* node, int key)
{
	Hash_table* hash_table = node->hash_table;
	while (hash_table != NULL && hash_table->key != key) {
		hash_table = hash_table->next;
	}
	return hash_table;
}

//Hash table
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

int hash(char* value)
{
	int sum = 0;
	for (int i = 0; i < strlen(value); i++)
	{
		sum += (value[i] * i);
	}
	printf("%d\n", sum);
	sum = sum % KEYSPACE;
	return sum;
}

void add_value(List_node *list_node, char *value)
{
	int key = hash(value);
	printf("%d\n", key);

	Node* node = search_key_in_node(list_node, key);
	if (node == NULL) {
		printf("Error\n");
		return;
	}
	create_node_hash_table(node, key, value);
}

//Print
void print_dht(List_node* list_node)
{
	Node* node = list_node->first_node;

/*	move(1, 0);
	printw("Left");
	move(2, 0);
	printw("Node");
	move(3, 0);
	printw("Right");
*/
	for (int i = 0; i < list_node->number_node; i++)
	{
		printf("%p\t", node->left);
		printf("%p\t", node);
		printf("%p\t", node->right);
		printf("%d\t", node->id);
		printf("%d\t", node->border);

		if (node->hash_table != NULL) {
			printf("\n");
			Hash_table *hash_table = node->hash_table;
			while (hash_table != NULL) {
				printf("%d\t%s\n", hash_table->key, hash_table->value);
				hash_table = hash_table->next;
			}
		}
		printf("\n");

/*		move(0, i * 10 + 10);
		printw("Node-%d", i);
		move(1, i * 10 + 10);
		printw("%p", node->left);
		move(2, i * 10 + 10);
		printw("%p", node);
		move(3, i * 10 + 10);
		printw("%p", node->right);
*/		
		node = node->right;
	}
}