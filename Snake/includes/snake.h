#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>


#define WIDTH 40
#define HEIGHT 9
#define SNAKE_LEN 6
#define H_GRID 20
#define W_GRID 40

#define DARK_ORANGE "\033[38;5;130m"
#define GREEN   "\033[32m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

typedef enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } t_dir;

typedef struct s_point {
    int x;
    int y;
} t_point;

typedef struct s_player {
    int id;
    char *name;
    int score;
    int highScore;
    int rank;
    struct s_player *prev;
} t_player;

typedef struct s_ball {
    int x;
    int y;
} t_ball;

typedef struct s_game {
    int x;
    int y;
    struct s_ball *ball;
    bool start;
    int size;
    t_point body[(H_GRID - 2) * (W_GRID - 2)];
} t_game;

// border.c
void get_border_pos(int t, int *x, int *y);
void draw_frame(int step);

// player.c
void init_player(t_player *player, t_player *prev);
void set_name(t_player *player);

// map.c

int play(t_player *player, t_game *game);
void draw_map(int head_pos, char grid[H_GRID][W_GRID], int prev_score, t_player *player, t_game *game);
void get_border_map(int t, int *x, int *y);
void init_game(t_game *game);
void generate_apple(char grid[H_GRID][W_GRID], t_game *game);
int check_valid(t_game *game);

// keyboard.c

void move_player(t_game *game, t_dir dir);
void handle_input(t_dir *dir);
void restore_terminal_mode(struct termios *old_term);
void set_noncanonical_mode(struct termios *old_term);