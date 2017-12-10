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

	add_value(list_node, "testrrghyjchgrsf");
	//getch();

	//endwin();
	return 0;
}