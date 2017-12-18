#include "DHT.h"

void menu()
{
	List_node *list_node = NULL;
	int act;

	while (act != 10) {
		printf("\n1) Create DHT\n");
		printf("2) Print DHT\n");
		printf("3) Delete DHT\n");
		printf("4) Info first node\n");
		printf("5) Change first node DHT\n");
		printf("6) Add node in DHT\n");
		printf("7) Delete node from DHT\n");
		printf("8) Add value\n");
		printf("9) Search value\n");
		printf("10) Exit\n");

		printf("Input act: ");
		scanf("%d", &act);
		printf("\n");

		switch (act)
		{
			case 1:
				if (list_node == NULL) {
					int number;
					printf("Input the number of nodes: ");
					scanf("%d", &number);
					list_node = create_list_node(number);
				} else {
					printf("Error. DHT already exists.\n");
				}
				break;
			case 2:
				if (list_node != NULL) {
					print_dht(list_node);
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 3:
				if (list_node != NULL) {
					delete_dht(list_node);
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 4:
				if (list_node != NULL) {
					info_first_node(list_node);
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 5:
				if (list_node != NULL) {
					int num;
					printf("Input the node number: ");
					scanf("%d", &num);
					change_first_node(list_node, num);
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 6:
				if (list_node != NULL) {
					//
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 7:
				if (list_node != NULL) {
					//
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 8:
				if (list_node != NULL) {
					//char *value = malloc(sizeof);
					//fgets(value, 100, stdin);
					//add_value(list_node, value);
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 9:
				if (list_node != NULL) {
					//char *value;
					//fgets(value, 100, stdin);
					//search_value(list_node, value);
				} else {
					printf("Error. DHT not exists.\n");
				}
				break;
			case 10:
				printf("Exit\n");
				break;
			default:
				printf("Act not found.\n");
		}
	}

}

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

void change_first_node(List_node *list_node, int number)
{
	for (int i = 0; i < number; ++i)
	{
		list_node->first_node = list_node->first_node->right;
	}
}

void info_first_node(List_node* list_node)
{
	Node* node = list_node->first_node;

	printf("///First node///\n");
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

	if (node->routing_table != NULL) {
		printf("\nRouting table\n");
		Routing_table *routing_table = node->routing_table;
		while (routing_table != NULL) {
			printf("%p\t%d\n", routing_table->node, routing_table->key);
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
	printf("///Search value///\nNode: %p\nId: %d\n", node, node->id);
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
	//free(list_node);
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
	node->hash_table = NULL;
	node->routing_table = NULL;

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
	//free(node);
}

void delete_node(List_node* list_node, Node* node)
{
	change_first_node(list_node, 1);
	free_node(node);
	list_node->number_node--;
}

//Print
void print_dht(List_node* list_node)
{
	Node* node = list_node->first_node;

	printf("///Print DHT///\n");

	for (int i = 0; i < list_node->number_node && node != NULL; i++)
	{
		printf("%p\t", node->left);
		printf("%p\t", node);
		printf("%p\t", node->right);
		printf("%d\t", node->id);
		printf("%d\t", node->border);

		if (node->hash_table != NULL) {
			printf("\nHash_table\n");
			Hash_table *hash_table = node->hash_table;
			while (hash_table != NULL) {
				printf("%d\t%s\n", hash_table->key, hash_table->value);
				hash_table = hash_table->next;
			}
		}

		if (node->routing_table != NULL) {
			printf("\nRouting table\n");
			Routing_table *routing_table = node->routing_table;
			while (routing_table != NULL) {
				printf("%p\t%d\n", routing_table->node, routing_table->key);
			}
		}
		printf("\n");	
		node = node->right;
	}
}