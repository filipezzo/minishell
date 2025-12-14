NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SLIB_DIR = lib
EXEC_DIR = exec
LIBFT_DIR = libft
INCLUDE_DIR = include
UTILS_DIR = utils
MOCK_DIR = mock

EXEC = $(BIN_DIR)/$(NAME)

SRC_FILES = main.c

EXEC_FILES = builtin.c builtin_echo.c builtin_pwd.c builtin_env.c builtin_export.c builtin_unset.c redirect.c	\
			 builtin_exit.c builtin_cd.c

MOCK_FILES = init_mock_env.c 
UTIL_FILES = linked_list.c utils_env.c clean.c

LIBFT = $(SLIB_DIR)/libft.a

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
       $(addprefix $(SRC_DIR)/$(EXEC_DIR)/, $(EXEC_FILES)) \
	   $(addprefix $(SRC_DIR)/$(MOCK_DIR)/, $(MOCK_FILES)) \
	   $(addprefix $(SRC_DIR)/$(UTILS_DIR)/, $(UTIL_FILES))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER = $(INCLUDE_DIR)/minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
IFLAGS = -I $(INCLUDE_DIR)
RM = rm -rf

all: $(EXEC)

$(EXEC): $(LIBFT) $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(EXEC)
	@echo "[\033[0;32mOK\033[0m] $(NAME) compilado em $(BIN_DIR) 👌👌😍"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "[\033[0;32mOK\033[0m] Compilado: $< ✅"

$(LIBFT):
	@make -C $(SRC_DIR)/$(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[\033[0;31mOK\033[0m] Arquivos objeto limpos."

fclean: clean
	@$(RM) $(BIN_DIR)
	@$(RM) $(SLIB_DIR)
	@echo "[\033[0;31mOK\033[0m] Limpeza completa."

re: fclean all

.PHONY: all clean fclean re