#include "headers/init.h"
#include "headers/interface.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void build_selection_menu(WINDOW *, struct network_interfaces *, int, int);

int main(int argc, char **argv) {
  printf("Attempting to find interfaces...\n");
  struct network_interfaces network_interfaces = find_interfaces();
  for (int i = 0; i < network_interfaces.num_interfaces; ++i) {
    printf("Interface Name: %s\n", network_interfaces.interface_names[i]);
  }

  WINDOW *main_window = init_curses();

  int maxX, maxY;
  getmaxyx(main_window, maxY, maxX);

  build_selection_menu(main_window, &network_interfaces, maxX, maxY);
  getch();

  free_interface_names(&network_interfaces);
  endwin();
  return 0;
}

void build_selection_menu(WINDOW *main_window,
                          struct network_interfaces *interfaces, int maxX,
                          int maxY) {
  struct interface_section *sections = (struct interface_section *)malloc(
      sizeof(struct interface_section) * interfaces->num_interfaces);
  for (int i = 0, col = 0, row = 0; i < interfaces->num_interfaces; ++i) {
    sections[i] = build_interface_section(main_window, col, maxX/MAX_COLS, 25, row);
    create_box(&sections[i]);
    if(col++ == MAX_COLS - 1){
        row++;
        col = 0;
    }
  }
  refresh();
}
