#include <ncurses.h>
struct interface_section {
  WINDOW* window;
  struct interface_border;
  int startx, starty, height, width;
};

struct interface_border {
chtype top_right, bottom_right, top_left, bottom_left, right_side, left_side, top, bottom;
};


WINDOW *init_curses() {
  WINDOW *window = initscr();
  int c_break_init = cbreak(), 
    keypad_init = keypad(stdscr, true);

  if(c_break_init != 0){
      printf("Error initializing cbreak for ncurses.");      
      exit(1);
  }

  if(keypad_init != 0){
      printf("Error initializing keypad for ncurses.");      
      exit(1);
  }

  return window;
}

struct interface_section* init_section(WINDOW* window, int startx, int starty, int width, int height){
  struct interface_section* new_section;
  new_section->height = height;
  new_section->width = width;
  new_section->startx = startx;
  new_section->starty = starty;
  new_section->window = window;
  return new_section;
}

struct interface_border* init_border(chtype corner, chtype side, chtype top_bottom){
  struct interface_border* new_border;
  new_border->top_left = corner;
  new_border->top_right = corner;
  new_border->bottom_left = corner;
  new_border->bottom_right = corner;
  new_border->left_side = side;
  new_border->right_side = side;
  new_border->top = top_bottom;
  new_border->bottom = top_bottom; 
  return new_border;
}

struct interface_section* build_interface_section(WINDOW* main_window, int win_id, int width, int height){
  int starty = height * win_id, startx = width * win_id;
  WINDOW* new_win = newwin(height, width, starty, startx);

  struct interface_section* new_section = init_section(new_win, startx, startx, width, height);
  return new_section;
}

void create_box(struct interface_section* section){
 
}
