#include "../headers/init.h"
#include <ncurses.h>

const int_fast8_t MAX_COLS = 4;

WINDOW *init_curses() {
  WINDOW *window = initscr();
  int c_break_init = cbreak(), keypad_init = keypad(stdscr, true);

  if (c_break_init != 0) {
    printf("Error initializing cbreak for ncurses.");
    exit(1);
  }

  if (keypad_init != 0) {
    printf("Error initializing keypad for ncurses.");
    exit(1);
  }

  return window;
}

struct interface_section init_section(WINDOW *window, int startx, int starty,
                                      int width, int height) {
  struct interface_section new_section;
  new_section.height = height;
  new_section.width = width;
  new_section.startx = startx;
  new_section.starty = starty;
  new_section.window = window;
  return new_section;
}

struct interface_border init_border(chtype corner, chtype side,
                                    chtype top_bottom) {
  struct interface_border new_border;
  new_border.top_left = corner;
  new_border.top_right = corner;
  new_border.bottom_left = corner;
  new_border.bottom_right = corner;
  new_border.left_side = side;
  new_border.right_side = side;
  new_border.top = top_bottom;
  new_border.bottom = top_bottom;
  return new_border;
}

struct interface_section build_interface_section(WINDOW *main_window,
                                                 int win_id, int width,
                                                 int height, int row) {
  int starty = height * row, startx = width * win_id;
  WINDOW *new_win = newwin(height, width, starty, startx);
  box(new_win, 0, 0);
  wrefresh(new_win);

  struct interface_section new_section =
      init_section(new_win, startx, starty, width, height);
  struct interface_border new_border = init_border('+', '|', '-');
  new_section.border = new_border;
  return new_section;
}

void create_box(struct interface_section *section) {
  int x = section->startx, y = section->starty, width = section->width,
      height = section->height;

  mvaddch(y, x, section->border.top_left);
  mvaddch(y, x + width, section->border.top_right);
  mvaddch(y + height, x + width, section->border.bottom_right);
  mvaddch(y + height, x, section->border.bottom_left);
  mvhline(y, x + 1, section->border.top, width - 1);
  mvhline(y + height, x + 1, section->border.bottom, width - 1);
  mvvline(y + 1, x, section->border.left_side, height - 1);
  mvvline(y + 1, x + width, section->border.right_side, height - 1);
}