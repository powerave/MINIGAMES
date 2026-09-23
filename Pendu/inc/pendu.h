#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *choose_word();
int check_word(char *s);
void init(char *res, char *word);
char *check_letter(char *word, char *res, char c);