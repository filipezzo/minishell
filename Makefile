NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
EXEC_DIR = exec
LIBFT_DIR = libft
INCLUDE_DIR = include
UTILS_DIR = utils
MOCK_DIR = mock

EXEC = $(BIN_DIR)/$(NAME)

SRC_FILES = main.c

EXEC_FILES = builtin.c builtin_echo.c builtin_pwd.c builtin_env.c builtin_unset.c redirect.c 

LIBFT_FILES = ft_add_nd_dlist.c ft_destroy_dlist.c ft_isascii.c ft_memcmp.c \
			ft_putchar_fd.c ft_split.c ft_strlcat.c ft_strrchr.c ft_atoi.c \
			ft_findin_bnode.c ft_isdigit.c ft_memcpy.c ft_putendl_fd.c \
			ft_strchr.c ft_strlcpy.c ft_strtrim.c ft_atol.c ft_foreach_dlist.c \
			ft_isprint.c ft_memmove.c ft_putnbr_fd.c ft_strcmp.c ft_strlen.c \
			ft_substr.c ft_bzero.c ft_get_next_line.c ft_isspace.c ft_memset.c \
			ft_putstr_fd.c ft_strdup.c ft_strmapi.c ft_tolower.c ft_calloc.c \
			ft_isalnum.c ft_itoa.c ft_new_bnode.c ft_remove_nd_dlist.c \
			ft_striteri.c ft_strncmp.c ft_toupper.c ft_destroy_bnode.c \
			ft_isalpha.c ft_memchr.c ft_new_dlist.c ft_setdir_bnode.c \
			ft_strjoin.c ft_strnstr.c

MOCK_FILES = init_mock_env.c
UTIL_FILES = free_env.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
       $(addprefix $(SRC_DIR)/$(EXEC_DIR)/, $(EXEC_FILES)) \
	   $(addprefix $(SRC_DIR)/$(LIBFT_DIR)/, $(LIBFT_FILES)) \
	   $(addprefix $(SRC_DIR)/$(MOCK_DIR)/, $(MOCK_FILES)) \
	   $(addprefix $(SRC_DIR)/$(UTILS_DIR)/, $(UTIL_FILES))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER = $(INCLUDE_DIR)/minishell.h

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
	@mkdir -p $(dir $@)
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