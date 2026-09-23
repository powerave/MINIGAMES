#include "../includes/snake.h"

void get_border_pos(int t, int *x, int *y) {
    int perimeter = 2 * (WIDTH + HEIGHT) - 4;
    t = (t % perimeter + perimeter) % perimeter;

    if (t < WIDTH) {
        // gauche a droite (bord superieur)
        *x = t;
        *y = 0;
    } else if (t < WIDTH + HEIGHT - 1) {
        // haut en bas (bord droit)
        *x = WIDTH - 1;
        *y = t - WIDTH + 1;
    } else if (t < 2 * WIDTH + HEIGHT - 2) {
        // droite a gauche (bord inferieur)
        *x = WIDTH - 1 - (t - (WIDTH + HEIGHT - 1));
        *y = H_GRID - 1;
    } else {
        // bas en haut (bord gauche)
        *x = 0;
        *y = HEIGHT - 1 - (t - (2 * WIDTH + HEIGHT - 3));
    }
}

void draw_frame(int step) {
    char grid[HEIGHT][WIDTH];
    int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1)
                grid[y][x] = '#';
            else
                grid[y][x] = ' ';
        }
    }

    for (int i = SNAKE_LEN - 1; i >= 0; i--) {
        get_border_pos(step - i, &x, &y);
        grid[y][x] = (i == 0) ? 'O' : 'o';
    }
    printf("\033[H" GREEN);

    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            if (y == HEIGHT / 2 && x == (WIDTH - 16) / 2) {
                printf(BOLD "Welcome to Snake" RESET GREEN);
                x += 15; // sauter la longueur du msg
            } else if (grid[y][x] == 'O') {
                printf(DARK_ORANGE "O" RESET);
            } else if (grid[y][x] == 'o') {
                printf(DARK_ORANGE "o" RESET);
            } else if (grid[y][x] == '#') {
                printf(GREEN "#" RESET);
            } else {
                putchar(grid[y][x]);
            }
        }
        putchar('\n');
    }
    printf(RESET);
}
