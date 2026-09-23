#include "../includes/snake.h"

// Active la saisie instantanée des touches
void set_noncanonical_mode(struct termios *old_term) {
    struct termios new_term;
    tcgetattr(STDIN_FILENO, old_term);
    new_term = *old_term;
    new_term.c_lflag &= ~(ICANON | ECHO); // Pas de buffer de ligne, pas d'écho vidéo
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // Mode non-bloquant
}

void restore_terminal_mode(struct termios *old_term) {
    tcsetattr(STDIN_FILENO, TCSANOW, old_term);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void handle_input(t_dir *dir) {
    char buf[3];
    int n = read(STDIN_FILENO, buf, 3);
    if (n >= 3 && buf[0] == '\033' && buf[1] == '[') {
        if (buf[2] == 'A' && *dir != DIR_DOWN)  *dir = DIR_UP;    // Flèche Haut
        if (buf[2] == 'B' && *dir != DIR_UP)    *dir = DIR_DOWN;  // Flèche Bas
        if (buf[2] == 'C' && *dir != DIR_LEFT)  *dir = DIR_RIGHT; // Flèche Droite
        if (buf[2] == 'D' && *dir != DIR_RIGHT) *dir = DIR_LEFT;  // Flèche Gauche
    }
}

void move_player(t_game *game, t_dir dir) {
    if (dir == DIR_UP)    game->y--;
    if (dir == DIR_DOWN)  game->y++;
    if (dir == DIR_LEFT)  game->x--;
    if (dir == DIR_RIGHT) game->x++;
}
