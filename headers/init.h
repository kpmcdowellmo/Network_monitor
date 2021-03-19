#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
extern const int_fast8_t MAX_COLS;

struct interface_border {
  chtype top_right, bottom_right, top_left, bottom_left, right_side, left_side,
      top, bottom;
};
struct interface_section {
  WINDOW *window;
  struct interface_border border;
  int startx, starty, height, width;
  struct network_interface *network_interface;
};

// Function prototypes.
WINDOW *init_curses();
struct interface_section init_section(WINDOW*, int, int, int, int);
struct interface_border init_border(chtype, chtype, chtype);
struct interface_section build_interface_section(WINDOW*, int, int, int, int);
void render_information(struct interface_section*);
void create_box(struct interface_section*);
