NAME = minishell
EXEC = $(BIN_DIR)/$(NAME)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
UTILS_DIR = utils

SRC_FILES =	main.c	\
			

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
HEADER = $(addprefix $(INCLUDE_DIR)/, minishell.h )

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
IFLAGS = -I $(INCLUDE_DIR)
RM = rm -rf

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
	@echo "[\033[0;32mOK\033[0m] $(NAME) compilado em $(BIN_DIR) 👌👌😍"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "[\033[0;32mOK\033[0m] Compilado: $< ✅"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[\033[0;31mOK\033[0m] Arquivos objeto limpos."

fclean: clean
	$(RM) $(BIN_DIR)
	@echo "[\033[0;31mOK\033[0m] Limpeza completa."

re: fclean all

.PHONY: all clean fclean re