#include "../includes/snake.h"

void generate_apple(char grid[H_GRID][W_GRID], t_game *game) {
    

    do {
        // Tirer x entre 1 et W_GRID - 2 (pour éviter les murs)
        game->ball->x = (rand() % (W_GRID - 2)) + 1;
        // Tirer y entre 1 et H_GRID - 2 (pour éviter les murs)
        game->ball->y = (rand() % (H_GRID - 2)) + 1;

    // Recommencer si la case tirée n'est pas un espace vide
    } while (grid[game->ball->y][game->ball->x] != ' ');

    return;
}

void init_game(t_game *game) {
    game->x = 5;
    game->y = 5;
    game->ball = malloc(sizeof(t_ball));
    if (game->ball == NULL)
        return;
    game->ball->x = 0;
    game->ball->y = 0;
    game->start = false;
    game->size = 1;
    game->body[0].x = game->x;
    game->body[0].y = game->y;
}

void get_border_map(int t, int *x, int *y) {
    int perimeter = 2 * (W_GRID + H_GRID) - 4;
    t = (t % perimeter + perimeter) % perimeter;

    if (t < W_GRID) {
        // gauche a droite (bord superieur)
        *x = t;
        *y = 0;
    } else if (t < W_GRID + H_GRID - 1) {
        // haut en bas (bord droit)
        *x = W_GRID - 1;
        *y = t - W_GRID + 1;
    } else if (t < 2 * W_GRID + H_GRID - 2) {
        // droite a gauche (bord inferieur)
        *x = W_GRID - 1 - (t - (W_GRID + H_GRID - 2));
        *y = H_GRID - 1;
    } else {
        // bas en haut (bord gauche)
        *x = 0;
        *y = H_GRID - 1 - (t - (2 * W_GRID + H_GRID - 3));
    }
}

void draw_map(int head_pos, char grid[H_GRID][W_GRID], int prev_score, t_player *player, t_game *game) {
    int x;
    int y;
    int hs = 0;
    
    for (y = 0; y < H_GRID; y++) {
        for (x = 0; x < W_GRID; x++) {
            if (y == 0 || x == 0 || y == H_GRID - 1 || x == W_GRID - 1) {
                grid[y][x] = '#';
            } else {
                grid[y][x] = ' ';
            }
        }
    }
    for (int i = 0; i < game->size; i++) {
        if (game->body[i].x > 0 && game->body[i].y > 0 && game->body[i].x < W_GRID - 1 && game->body[i].y < H_GRID - 1) {
            grid[game->body[i].y][game->body[i].x] = (i == 0) ? '@' : '=';
        } 
    }
    if (game->start == false) {
        generate_apple(grid, game);
        game->start = true;
    }
    if (prev_score < player->score)
        generate_apple(grid, game);
    if (game->start == true) {
        grid[game->ball->y][game->ball->x] = 'x';
    }
    grid[game->y][game->x] = '@';
    for (int i = SNAKE_LEN - 1; i >= 0; i--) {
        get_border_map(head_pos - i, &x, &y);
        grid[y][x] = (i == 0) ? 'O' : 'o';
    }
    printf("\033[H");
    
    for(y = 0; y < H_GRID; y++) {
        for(x = 0; x < W_GRID; x++) {
            if (grid[y][x] == 'O') {
                printf(DARK_ORANGE "O" RESET);
            } else if (grid[y][x] == 'o') {
                printf(DARK_ORANGE "o" RESET);
            } else if (grid[y][x] == '#') {
                printf(GREEN "#" RESET);
            } else if (grid[y][x] == '@') {
                if (y == 0 || x == 0 || y == H_GRID - 1 || x == W_GRID - 1) {
                    printf("\033[31m" "@" RESET);
                } else {
                    printf("\033[33m" "@" RESET);
                }
            } else if (grid[y][x] == '=') {
                printf("\033[33m" "=" RESET);
            } else {
                putchar(grid[y][x]);
            }
        }

        if (y == 3) {
            printf("          -==*  %s  *==-", player->name);
        } else if (y == 5) {
            printf("               SCORE: %d", player->score);
        } else if (y == 6) {
            printf("           HIGHSCORE: %d", player->highScore);
        }
        if (check_valid(game) == 1) {
            if (player->highScore < player->score) {
                hs = 1;
                player->highScore = player->score;
            }
            if (y == 9 && hs == 1) {
                printf("        \\o/ \033[32mNew HighScore \033[37m\\o/ ");
            }
            if (y == 13) {
                if (game->y == 0 || game->x == 0 || game->y == H_GRID - 1 || game->x == W_GRID - 1) {
                    printf("     \033[31mYOU HIT THE BORDER AND DIED");
                } else {
                    printf("     \033[31mYOU BIT YOUR TAIL AND DIED");
                }
            } else if (y == 15) {
                printf("              TRY AGAIN");
            } else if (y == 17) {
                printf("     Do you want to restart ?(y/n):");
                hs = 0;
            }
        }

        printf("\033[K\n");
    }
}

int check_valid(t_game *game) {
    if (game->y == 0 || game->x == 0 || game->y == H_GRID - 1 || game->x == W_GRID - 1) {
        return 1;
    }
    for (int i = game->size - 1; i > 0; i--) {
        if (game->x == game->body[i].x && game->body[i].y == game->y)
        return 1;
    }
    return 0;
}

int play(t_player *player, t_game *game) {
    int head_pos = 0;
    char grid[H_GRID][W_GRID];
    t_dir dir = DIR_RIGHT;
    int prev_score = player->score;
    struct termios old_term;
    char choice;

    set_noncanonical_mode(&old_term);
    printf("\033[?25l\033[2J");
    while (1) {
        handle_input(&dir);
        move_player(game, dir);
        
        for (int i = game->size - 1; i > 0; i--)
        game->body[i] = game->body[i - 1];
        game->body[0].x = game->x;
        game->body[0].y = game->y;
        draw_map(head_pos, grid, prev_score, player, game);
        if (check_valid(game) == 1)
                break;
        
        if ((game->x == game->ball->x) && (game->y == game->ball->y)) {
            player->score++;
            game->size++;
            generate_apple(grid, game);
        }
        head_pos++;
        prev_score = player->score;
        fflush(stdout);
        usleep(100000);
    }
    restore_terminal_mode(&old_term);
    printf("\033[?25h");
    free(game->ball);
    if (scanf(" %c", &choice) != 1)
        return 0;
    if (choice == 'y' || choice == 'Y')
        return 1;
    return 0;
}