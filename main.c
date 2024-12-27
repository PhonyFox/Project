#include <ncurses.h>

int main() {
    initscr();
    cbreak();
    noecho();
    printw("Hello World!");
    int ch = getch();

    printw("\nYou entered:");
    printw("%c", ch);
    refresh();
    getch();
    endwin();
    return 0;
}

