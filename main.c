#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct {
    char name[50];
    char username[50];
    char email[50];
    char deathday[20];
} User;

void initscreen();
void createuser();
void loaduser();
void cleanup();

int main() {
    int choice;
    initscreen();

    while (1) {
        mvprintw(1, 2, "=== Victims Management Menu ===");
        mvprintw(3, 4, "1. Create New Victim");
        mvprintw(4, 4, "2. Load Victim");
        mvprintw(5, 4, "3. Exit");
        mvprintw(7, 4, "4. Enter your choice:");
        refresh();

        scanw("%d", &choice);

        switch (choice) {
            case 1:
                createuser();
                break;
            case 2:
                loaduser();
                break;
            case 3:
                cleanup();
                exit(0);
            default:
                mvprintw(0, 1, "You cannot delay your death by entering invalid choice!");
                getch();

        }

    }

    return 0;
}

void initscreen() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void cleanup() {
    endwin();
}

void createuser() {
    User user;
    char filename[100];
    FILE *file;

    clear();
    mvprintw(1, 2, "=== Create New User ===");
    mvprintw(3, 2, "Enter name: ");
    echo();
    getnstr(user.name, sizeof(user.name) - 1);

    mvprintw(4, 2, "Enter username: ");
    getnstr(user.username, sizeof(user.username) - 1);

    mvprintw(5, 2, "Enter email: ");
    getnstr(user.email, sizeof(user.email) - 1);

    mvprintw(5, 2, "Enter your death day of the week: ");
    getnstr(user.deathday, sizeof(user.email) - 1);

    snprintf(filename, sizeof(filename), "%s.txt", user.username);

    file = fopen(filename, "w");
    if (file == NULL) {
        mvprintw(7, 2, "Error creating user file!");
        getch();
        return;
    }
    fprintf(file, "Name: %s\n", user.name);
    fprintf(file, "Username: %s\n", user.username);
    fprintf(file, "Email: %s\n", user.email);
    fprintf(file, "Deathday: %s\n", user.deathday);
    fclose(file);

    mvprintw(7, 2, "User '%s' created successfully! Press any key to continue...", user.username);
    getch();


}

void loaduser() {
    char username[50];
    char filename[100];
    char line[200];
    FILE *file;

    clear();
    mvprintw(1, 2, "=== Load User ===");
    mvprintw(3, 2, "Enter username to load: ");
    echo();
    getnstr(username, sizeof(username) - 1);
    noecho();

    snprintf(filename, sizeof(filename), "%s.txt", username);

    file = fopen(filename, "r");
    if (file == NULL) {
        mvprintw(5, 2, "Error: User file not found! Press any key to return...");
        getch();
        return;
    }

    clear();
    mvprintw(1, 2, "=== User Details ===");
    int row = 3;
    while (fgets(line, sizeof(line), file)) {
        mvprintw(row++, 2, "%s", line);
    }
    fclose(file);

    mvprintw(row + 1, 2, "Press any key to return...");
    getch();
}



//
// #include <ncurses.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// // ساختار کاربر
// typedef struct {
//     char name[50];
//     char username[50];
//     char email[100];
// } User;
//
// // توابع کمکی
// void initScreen();
// void createUser();
// void loadUser();
// void cleanup();
//
// int main() {
//     int choice;
//
//     // مقداردهی اولیه ncurses
//     initScreen();
//
//     while (1) {
//         clear(); // پاک کردن صفحه
//         mvprintw(1, 2, "=== User Management Menu ===");
//         mvprintw(3, 4, "1. Create New User");
//         mvprintw(4, 4, "2. Load User");
//         mvprintw(5, 4, "3. Exit");
//         mvprintw(7, 4, "Enter your choice: ");
//         refresh();
//
//         // دریافت انتخاب کاربر
//         scanw("%d", &choice);
//
//         switch (choice) {
//             case 1:
//                 createUser();
//                 break;
//             case 2:
//                 loadUser();
//                 break;
//             case 3:
//                 cleanup();
//                 exit(0);
//             default:
//                 mvprintw(9, 4, "Invalid choice! Press any key to try again...");
//                 getch();
//         }
//     }
//
//     return 0;
// }
//
// // مقداردهی اولیه ncurses
// void initScreen() {
//     initscr();          // شروع ncurses
//     cbreak();           // غیرفعال کردن بافر خطی
//     noecho();           // عدم نمایش ورودی کاربر
//     keypad(stdscr, TRUE); // فعال کردن کلیدهای خاص (مثل جهت‌ها)
// }
//
// // تابع پاکسازی ncurses
// void cleanup() {
//     endwin(); // پایان ncurses
// }
//
// // تابع ایجاد کاربر جدید
// void createUser() {
//     User user;
//     char filename[100];
//     FILE *file;
//
//     clear();
//     mvprintw(1, 2, "=== Create New User ===");
//     mvprintw(3, 2, "Enter name: ");
//     echo(); // فعال کردن نمایش ورودی
//     getnstr(user.name, sizeof(user.name) - 1);
//
//     mvprintw(4, 2, "Enter username: ");
//     getnstr(user.username, sizeof(user.username) - 1);
//
//     mvprintw(5, 2, "Enter email: ");
//     getnstr(user.email, sizeof(user.email) - 1);
//     noecho(); // غیرفعال کردن نمایش ورودی
//
//     // ایجاد نام فایل
//     snprintf(filename, sizeof(filename), "%s.txt", user.username);
//
//     // ذخیره اطلاعات کاربر در فایل
//     file = fopen(filename, "w");
//     if (file == NULL) {
//         mvprintw(7, 2, "Error creating user file!");
//         getch();
//         return;
//     }
//
//     fprintf(file, "Name: %s\n", user.name);
//     fprintf(file, "Username: %s\n", user.username);
//     fprintf(file, "Email: %s\n", user.email);
//     fclose(file);
//
//     mvprintw(7, 2, "User '%s' created successfully! Press any key to continue...", user.username);
//     getch();
// }
//
// // تابع بارگذاری اطلاعات کاربر
// void loadUser() {
//     char username[50];
//     char filename[100];
//     char line[200];
//     FILE *file;
//
//     clear();
//     mvprintw(1, 2, "=== Load User ===");
//     mvprintw(3, 2, "Enter username to load: ");
//     echo();
//     getnstr(username, sizeof(username) - 1);
//     noecho();
//
//     snprintf(filename, sizeof(filename), "%s.txt", username);
//
//     file = fopen(filename, "r");
//     if (file == NULL) {
//         mvprintw(5, 2, "Error: User file not found! Press any key to return...");
//         getch();
//         return;
//     }
//
//     clear();
//     mvprintw(1, 2, "=== User Details ===");
//     int row = 3;
//     while (fgets(line, sizeof(line), file)) {
//         mvprintw(row++, 2, "%s", line);
//     }
//     fclose(file);
//
//     mvprintw(row + 1, 2, "Press any key to return...");
//     getch();
// }
