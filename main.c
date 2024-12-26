#include <ncurses.h>

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    printw("He d llo Racy! Thi    s game will scare you :)");
    attroff(COLOR_PAIR(1));
    refresh();
    getch();
    endwin();
    return 0;
}