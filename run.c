#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

// define colors
// except dont they come in the header file

#define PAIR_GREEN_BLACK 1
#define PAIR_YELLOW_BLACK 2

#define DELAY 35000

// defined const color pairs here
// colors are a pair of foreground and background
//

int main(void) {

  // intiialize curses

  initscr();
  // stdscr is the default window you can add subsets
  keypad(stdscr, TRUE);
  // cbreak disables line buffering so we get
  // straight up input like esc chars etc
  cbreak();
  // dont echo inputs to term
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(FALSE);

  if (has_colors() == FALSE) {
    // endwin returns the term to normal behavior
    endwin();
    printf("Terminal does not support colors");
    exit(1);
  }

  // start color allows the term to use colors
  // each color has a foreground and
  // a background value
  start_color();
  init_pair(PAIR_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
  init_pair(PAIR_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);

  clear();

  int max_y = 0, max_x = 0;
  int actor_y = 0, actor_x = 0;
  int floor_y = 0, floor_x = 0;

  int next_x = 0;

  // get initial dimensions so we cna place our actor
  getmaxyx(stdscr, max_y, max_x);

  // set our floor to be halfway

  floor_y = max_y / 2;

  // todo:
  // print floor from the right

  // then drop the guy on the floor after a few come on screen
  // then make things hit it
  // then make hops

  // main loop

  int ch; // input

  int direction = 1;

  floor_y = max_y / 2;

  do {

    ch = getch();

    getmaxyx(stdscr, max_y, max_x);

    // if we are taller than the floor descend
    if (floor_y < max_y / 2) {
      floor_y += 1;
    }

    clear();
    attron(COLOR_PAIR(PAIR_GREEN_BLACK));
    mvprintw(floor_y, floor_x, "=");
    attroff(COLOR_PAIR(PAIR_GREEN_BLACK));
    refresh();

    usleep(DELAY);

    next_x = floor_x + direction;

    if (next_x >= max_x || next_x < 0) {
      direction *= -1;
    } else {
      floor_x += direction;
    }

    if (ch == ' ') {
      floor_y -= 11;
    }

  } while ((ch != 'q') && ch != 'Q');

  // wrap it up
  endwin();
  return 0;
}
