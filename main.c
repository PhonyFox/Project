#include <ncurses.h>
#include <stdlib.h>

typedef struct Room {
    int xPosition;
    int yPosition;
    int hight;
    int width;
    //Monster ** monster;
    //Item ** items;

} Room;


typedef struct Player {
    int xPosition;
    int yPosition;
    int health;
} Player;
int checkposition(int newX, int newY, Player * user);
int screensetup();
Room ** mapsetup();
Player * playersetup();
int handleinput(int input, Player * user);
int playermove(int y, int x, Player * user);
int drawroom(Room * room);


int main() {
    Player * user;
    int ch;
    screensetup();
    mapsetup();
    user = playersetup();
    while ((ch = getch()) != 'q') {
        handleinput(ch, user);
    }
    endwin();
    return 0;
}

int screensetup() {
    initscr();
    clear();
    printw("Welcome to NCurses!");
    noecho();
    refresh();

    return 1;

}

Room ** mapsetup() {
    clear();
    Room ** rooms;
    rooms = (Room **) malloc(sizeof(Room *) * 6);
    mvprintw(13, 13, "--------");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "--------");

    rooms[0] = createroom(13, 13, 6, 8);
    drawroom(rooms[0]);

    mvprintw(2, 40, "--------");
    mvprintw(3, 40, "|......|");
    mvprintw(4, 40, "|......|");
    mvprintw(5, 40, "|......|");
    mvprintw(6, 40, "|......|");
    mvprintw(7, 40, "--------");

    rooms[1] = createroom(40, 2, 6, 8);
    drawroom(rooms[1]);

    mvprintw(10, 40, "--------");
    mvprintw(11, 40, "|......|");
    mvprintw(12, 40, "|......|");
    mvprintw(13, 40, "|......|");
    mvprintw(14, 40, "|......|");
    mvprintw(15, 40, "--------");

    rooms[2] = createroom(40, 10, 6, 8);
    drawroom(rooms[2]);

    refresh();

    return rooms;
}

Room * createroom(int x, int y, int hight, int width) {
    Room * newroom;
    newroom = (Room *) malloc(sizeof(Room));
    newroom->xPosition = x;
    newroom->yPosition = y;
    newroom->hight = hight;
    newroom->width = width;
    return newroom;
}

int drawroom(Room * room) {
    int x;
    int y;

    for (x = room->xPosition; x < room->xPosition + room->width; x++) {
        mvprintw(room->yPosition, x, "-");
        mvprintw(room->yPosition + room->hight, x, "-");
    }

    return 1;
}

Player * playersetup() {
    Player * newPlayer = (Player *) malloc(sizeof(Player));

    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    playermove(14, 14, newPlayer);

    return newPlayer;
}

int handleinput(int input, Player * user) {
    int newY;
    int newX;
    switch (input) {
        case 'w':
        case 'W':
            newY = user->yPosition - 1;
            newX = user->xPosition;
            break;
        case 's':
        case 'S':
            newY = user->yPosition + 1;
            newX = user->xPosition;
            break;
        case 'a':
        case 'A':
            newY = user->yPosition;
            newX = user->xPosition - 1;
            break;
        case 'd':
        case 'D':
            newY = user->yPosition;
            newX = user->xPosition + 1;
            break;
        default:
            break;
    }

    checkposition(newY, newX, user);

}

int checkposition(int newY, int newX, Player * user) {
    int space;
    switch (mvinch(newY, newX)) {
        case '.':
            playermove(newY, newX, user);
            break;
        default:
            move(user->yPosition, user->xPosition);
            break;
    }
}

int playermove(int y, int x, Player * user) {
    mvprintw(user->yPosition, user->xPosition, ".");
    user->xPosition = x;
    user->yPosition = y;
    mvprintw(user->yPosition, user->xPosition, "@");
    move(user->yPosition, user->xPosition);
}