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
			border = ((999 / number) / 2);
		space = (999 / number) * i;
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

Node* search_node_for_insert(List_node *list_node, int key)
{
	Node *node = list_node->first_node;

	for (int i = 0; i < list_node->number_node; i++)
	{
		if (node->id != 0) {
			if ((node->id - node->border) < key && (node->id + node->border) > key) {
				return node;
			}
		} else {
			//для узла 0
			if ((999 - node->border) < key && (node->id + node->border) >= key) {
				return node;
			}
		}
		node = node->right;
	}
	return NULL;
}

//Hash table
void create_node_hash_table(Node *node, int key, char* value)
{
	Hash_table *routing_table = node->routing_table, *parent;
	
	while (routing_table != NULL) {
		parent = routing_table;
		routing_table = routing_table->next;
	}

	routing_table = malloc(sizeof(Hash_table));
	routing_table->key = key;
	routing_table->value = value;

	if (node->routing_table == NULL) {
		routing_table->next = NULL;
		routing_table->parent = NULL;
		node->routing_table = routing_table;
	} else {
		parent->next = routing_table;
		routing_table->parent = parent;
		routing_table->next = NULL;
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
	sum = sum % 999;
	return sum;
}

void add_value(List_node *list_node, char *value)
{
	int key = hash(value);
	printf("%d\n", key);

	Node* node = search_node_for_insert(list_node, key);
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

		if (node->routing_table != NULL) {
			printf("\n");
			Hash_table *routing_table = node->routing_table;
			while (routing_table != NULL) {
				printf("%d\t%s\n", routing_table->key, routing_table->value);
				routing_table = routing_table->next;
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