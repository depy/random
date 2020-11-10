#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Player {
    Position pos;
    int standingOn;
    int health;
} Player;

void setUpScreen();
void drawMap();

Player setUpPlayer();
void drawPlayer(Player player);
void movePlayer(Player *player, char dir);
void handleInput(int key, Player *player);

void debug(int key, Player player);
void inspectPlayer(Player player);
void inspectInput(int key);

int main() {
    int ch;
    Player player;

    setUpScreen();

    player = setUpPlayer(14, 14, 20);
    drawMap();
    drawPlayer(player);
    debug(' ', player);

    while((ch = getch()) != 'q') {
        handleInput(ch, &player);
        clear();

        drawMap();
        drawPlayer(player);
        debug(ch, player);
        refresh();
    }
    
    endwin();
    return 0;
}

void setUpScreen() {
    initscr();
    noecho();
    curs_set(0);
    refresh();
}

void drawMap() {
    mvprintw(13, 13, "--------");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "--------");

    mvprintw(2, 40, "--------");
    mvprintw(3, 40, "|......|");
    mvprintw(4, 40, "|......|");
    mvprintw(5, 40, "|......|");
    mvprintw(6, 40, "|......|");
    mvprintw(7, 40, "--------");

    mvprintw(10, 40, "------------");
    mvprintw(11, 40, "|..........|");
    mvprintw(12, 40, "|..........|");
    mvprintw(13, 40, "|..........|");
    mvprintw(14, 40, "|..........|");
    mvprintw(15, 40, "------------");
}

Player setUpPlayer(int startX, int startY, int startHealth) {
    Player newPlayer;

    newPlayer.pos.x = startX;
    newPlayer.pos.y = startY;
    newPlayer.health = startHealth;
    
    return newPlayer;
}

void handleInput(int key, Player *player) {
    switch(key) {
        case 'w': movePlayer(player, 'u'); break;
        case 's': movePlayer(player, 'd'); break;
        case 'a': movePlayer(player, 'l'); break;
        case 'd': movePlayer(player, 'r'); break;

        default:
            break;
    }
}

void movePlayer(Player *player, char dir) {
    Position move = {0, 0};

    switch(dir) {
        // Move up
        case 'u':
            move.x =  0;
            move.y = -1;  
            break;

        // Move down
        case 'd':
            move.x =  0;
            move.y =  1; 
            break;

        // Move left
        case 'l':
            move.x = -1;
            move.y =  0;
            break;

        // Move right
        case 'r':
            move.x =  1;
            move.y =  0;
            break;

        default:
            break;
    }

    int newX = player->pos.x + move.x;
    int newY = player->pos.y + move.y;
    int futurePosCh = mvinch(newY, newX);

    mvprintw(LINES-7, 0, "newX => %d", newX);
    mvprintw(LINES-8, 0, "newY => %d", newY);
    mvprintw(LINES-9, 0, "futurePosCh => '%c' (%d)", futurePosCh, futurePosCh);

    if((char)(futurePosCh) == '.') {
        player->pos.x = newX;
        player->pos.y = newY;
    }
}

void drawPlayer(Player player) {
    mvprintw(player.pos.y, player.pos.x, "@");
}



// Debug

void debug(int key, Player player) {
    inspectInput(key);
    inspectPlayer(player);
}

void inspectPlayer(Player player) {
    mvprintw(LINES-3, 0, "Player->pos.x => %d", player.pos.x);
    mvprintw(LINES-2, 0, "Player->pos.y => %d", player.pos.y);
    mvprintw(LINES-1, 0, "Player->health => %d", player.health);
}

void inspectInput(int key) {
    mvprintw(LINES-5, 0, "Key pressed => %c", key);
}