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
	int id;
	int border;
	struct Node *right;
	struct Node *left;
	struct Hash_table *hash_table;
} Node;

void create_node(List_node*, int, int);
void add_node_to_list(Node*, Node*);
Node* search_key_in_node(List_node*, int);


typedef struct Hash_table
{
	int key;
	char *value;
	struct Hash_table *next;
	struct Hash_table *parent;
} Hash_table;

void create_hash_table(Node*, int, char*);
int hash(char* value);
void add_value(List_node*, char*);
void add_node_hash_table(Node*);
Hash_table* search_key_in_table(Node*, int);


void print_dht(List_node*);

#endif