#include <stdio.h>
#include "DHT.h"

int main(int argc, char const *argv[])
{
	/*initscr();
	curs_set(0);
	//cbreak();
	keypad(stdscr, true);
	noecho();
	//nodelay(stdscr, true);
*/
	

	List_node *list_node = create_list_node(7);
	print_dht(list_node);

	add_value(list_node, "main");
	add_value(list_node, "test");
	add_value(list_node, "main_te");
	add_value(list_node, "my_test");
	add_value(list_node, "tesm1");
	add_value(list_node, "tee1");

	print_dht(list_node);
	//getch();

	//endwin();
	return 0;
}