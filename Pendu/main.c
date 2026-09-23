#include "inc/pendu.h"
#include "inc/display.h"

int main (void) {
    char *word;
    char c;
    int life = 6;
    int check_buffer;

    word = choose_word();
    if (!word)
        return 1;
    
    if (check_word(word) == 1)
        return 1;

    system("clear");

    char *res;

    res = calloc(strlen(word) + 1, sizeof(char));
    if (!res)
        return (printf("[Error] Calloc failed"), free(word), 1);
    
    init(res, word);

    while (strcmp(word, res) != 0 && life > 0) {
        printf("Choose a letter :");
        if (scanf(" %1c", &c) != 1) {
            free(res);
            free(word);
            return 1;
        }
        int extra_letters = 0;
        while ((check_buffer = getchar()) != '\n' && check_buffer != EOF)
            extra_letters++;
        if (extra_letters > 0) {
            printf("You can only type 1 character\n");
            continue;
        }
        if (c < 'a' || c > 'z') {
            printf ("Not a letter!\n");
            continue;
        }
        if (strchr(word, c) == NULL) {
            life--;
            printf("\nNo! You lost a life!\n\nLife Points: %d\n_______________________\n\n", life);
            display_hangman(life);
            if (life == 0)
                return(printf("You lost! 0 life left!\nThe word was --------> %s\n:'( try again !!", word), free(word), free(res), 0);
        }
        check_letter(word, res, c);
        printf("_______________________\n\n------> |  %s  | <------\n\n", res);
    }

    printf("You win !! You found the word :D\n");

    free(word);
    free(res);
    return 0;
}
