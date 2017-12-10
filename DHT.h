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
	float id;
	//struct Keyspace *keyspace;
	float border;
	struct Node *right;
	struct Node *left;
	struct Hash_table *routing_table;
} Node;

void create_node(List_node*, float, float);
void add_node_to_list(Node*, Node*);


typedef struct Hash_table
{
	//позиция на окружности(хешь)
	float key;
	char *value;
	struct Hash_table *next;
	struct Hash_table *parent;
} Hash_table;

void create_hash_table(Node*);
int hash(char* value);
void add_value(List_node*, char*);
//void add_node_hash_table(Node*)


typedef struct Keyspace
{
	//позиция на окружности(хешь) за которую отвечает узел
	float border;
} Keyspace;



void print_dht(List_node*);

#endif