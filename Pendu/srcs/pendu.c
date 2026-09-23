#include "../inc/pendu.h"

char *choose_word() {
    char *s;

    s = malloc(sizeof(char) * 30);
    if (!s)
        return (printf("[Error] Malloc failed"), NULL);
    printf("Choose a word and press 'Enter' :");
    scanf("%s", s);    
    return s;
}

int check_word(char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] < 'a' || s[i] > 'z')
            return (printf("[Error] Not a letter\n"), free(s), 1);
    }
    return 0;
}

void init(char *res, char *word) {
    int i = 0;
    for (i = 0; word[i]; i++)
        res[i] = '_';
    res[i] = '\0';
}

char *check_letter(char *word, char *res, char c) {
    for (int i = 0; word[i]; i++) {
        if (c == word[i])
            res[i] = c;
    }
    return res;
}