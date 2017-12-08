#ifndef DHT_H
#define DHT_H

#include <ncurses.h>

typedef struct List_node
{
	struct Node *first_node;
	int number_node;
} List_node;

List_node *create_list_node(int);


typedef struct Node
{
	//позиция на окружности(хешь)
	int id;
	struct Keyspace *keyspace;
	struct Node *right;
	struct Node *left;
	struct Hash_table *routing_table;
} Node;

void create_node(List_node*, int);
void add_node_to_list(Node*, Node*);


typedef struct Hash_table
{
	//позиция на окружности(хешь)
	int key;
	char *value;
	struct Hash_table *next;
	struct Hash_table *parent;
} Hash_table;

void create_hash_table(Node*);
//void add_node_hash_table(Node*)


typedef struct Keyspace
{
	//позиция на окружности(хешь) за которую отвечает узел
	int left_border;
	//позиция на окружности(хешь) за которую отвечает узел
	int right_border;
} Keyspace;



void print_dht(List_node*);

#endif