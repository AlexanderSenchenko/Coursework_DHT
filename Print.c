#include "DHT.h"

void print_dht(List_node* list_node)
{
	Node* node = list_node->first_node;

	printf("\n///Print DHT///\n");

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
		printf("\n");	
		node = node->right;
	}
}