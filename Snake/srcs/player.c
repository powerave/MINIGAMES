#include "../includes/snake.h"

void init_player(t_player *player, t_player *prev) {
    player->name = NULL;
    player->score = 0;
    player->highScore = 0;
    //player->next = NULL;
    player->rank = 0;

    if(prev) {
        player->id = prev->id + 1;
        //prev->next = player;
    } else {
        player->id = 0;
    }
    player->prev = prev;
}

void set_name(t_player *player) {
    player->name = calloc(20, sizeof(char));
    if (player->name == NULL)
        return;
    printf("Chose name: ");
    scanf("%19s", player->name);
    printf("\n________________\n| %s\n", player->name);
    printf("| High Score: %d\n", player->highScore);
    printf("| Rank: ");
    if (player->rank == 0)
        printf("Unranked\n");
    else
        printf("Rank: %d\n", player->rank);
    printf("________________\n");
}

