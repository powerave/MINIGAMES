#include "includes/snake.h"

int main() {
    printf("\033[?25l"); // masquer le curseur
    printf("\033[2J"); // clear l'ecran au debut
    int restart;

    for (int step = 0; step < 60; step++) {
        draw_frame(step);
        fflush(stdout);
        usleep(100000);
    }
    printf("\033[?25h\n");

    t_player    player;
    t_game      game;

    init_player(&player, NULL);
    set_name(&player);
    do {
        player.score = 0;
        init_game(&game);
        restart = play(&player, &game);
    } while (restart == 1);
    free(player.name);
    printf("THANK YOU FOR PLAYING\n");
    return 0;
}
