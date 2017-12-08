#include "DHT.h"
#include <stdio.h>
#include <stdlib.h>

#define KEYSPACE 1000

//List_node
List_node *create_list_node(int number)
{
	List_node *list_node = malloc(sizeof(List_node));
	if (list_node == NULL)
		return NULL;

	for (int i = 0; i < number; i++)
	{
		//не забыть про определение всего пространства
		//ключей и распределить по нему узлы
		//
		int space = (1000 / number) * i;
		//printf("%d\n", space);
		create_node(list_node, space);
	}
	list_node->number_node = number;

	return list_node;
}


//Node
void create_node(List_node *list_node, int space)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL)
		return;

	node->right = node;
	node->left = node;

	//присвотить узлу id
	node->id = space;
	//после определить область ответственности
	//создать таблицу маршрутизации
	//create_hash_table(node);

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

//Hash table
void create_hash_table(Node *node)
{
	Hash_table *routing_table = malloc(sizeof(Hash_table));
	if (routing_table == NULL)
		return;
	
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
		printf("%p\t%p\t%p\t%d\n", node->left, node, node->right, node->id);
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