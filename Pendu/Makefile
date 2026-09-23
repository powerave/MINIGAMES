# Nom de l'exécutable final
NAME        = pendu

# Compilateur et flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinc

# Dossiers
SRC_DIR     = srcs
OBJ_DIR     = objs
INC_DIR     = inc

# Fichiers sources et objets
# (On ajoute pendu.c qui doit contenir les fonctions du header)
SRCS        = main.c $(SRC_DIR)/pendu.c $(SRC_DIR)/display.c
OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Header pour la dépendance
HEADERS     = $(INC_DIR)/pendu.h

# Règle principale
all: $(NAME)

# Liaison des objets pour créer l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✨ Exécutable $(NAME) créé avec succès !"

# Compilation des fichiers .c en .o
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJ_DIR)
	@echo "🧹 Fichiers objets supprimés."

# Nettoyage complet (objets + exécutable)
fclean: clean
	rm -f $(NAME)
	@echo "🗑️  Exécutable $(NAME) supprimé."

# Recompiler tout à zéro
re: fclean all

# Évite les conflits si des fichiers portent le même nom qu'une règle
.PHONY: all clean fclean re