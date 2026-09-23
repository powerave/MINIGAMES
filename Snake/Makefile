NAME = snake

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC = main.c srcs/border.c srcs/player.c srcs/map.c srcs/keyboard.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re