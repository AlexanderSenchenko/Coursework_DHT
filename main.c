#include <stdio.h>
#include "DHT.h"

int main(int argc, char *argv[])
{
	//menu();

	List_node *list_node = create_list_node(7);
	print_dht(list_node);

	add_value(list_node, "main");
	add_value(list_node, "tezz");
	add_value(list_node, "main_te");
	add_value(list_node, "my_test");
	add_value(list_node, "tesm1");
	add_value(list_node, "tee1");
	add_value(list_node, "t2");
	add_value(list_node, "t7");

	print_dht(list_node);

	delete_node(list_node, 1);
	print_dht(list_node);

	//delete_node(list_node, 1);
	//print_dht(list_node);

	/*info_first_node(list_node);

	change_first_node(list_node, 2);
	info_first_node(list_node);*/
	

	search_value(list_node, argv[1]);
	return 0;
}