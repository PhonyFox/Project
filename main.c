#include <ncurses.h>

int main() {
    initscr();
    move(5, 10);
    printw("Hello World!");
    refresh();
    getch();
    endwin();
    return 0;
}

