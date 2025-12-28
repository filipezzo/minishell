NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INIT_DIR = init
SLIB_DIR = lib
INST_DIR = instance
FRONT_DIR = front
EXEC_DIR = exec
BUILTIN_DIR = builtin
LIBFT_DIR = libft
INCLUDE_DIR = include
UTILS_DIR = utils
MOCK_DIR = mock
SIGNAL_DIR = signals

EXEC = $(BIN_DIR)/$(NAME)

SRC_FILES = main.c

INST_FILES = lexunit.c prompt.c siglexer.c
FRONT_FILES = syntax_analyze.c build_dir_pmt.c build_home_pmt.c \
			build_host_pmt.c build_prompt.c build_type_pmt.c build_user_pmt.c \
			syntax_check_redir.c lexer.c parser.c start_prompt.c \
			syntax_check.c syntax_error_msg.c
BUILTIN_FILES = builtin.c builtin_echo.c builtin_pwd.c builtin_env.c builtin_export.c builtin_unset.c \
			 builtin_exit.c builtin_cd.c
EXEC_FILES = executor.c redirect.c execute_external.c
MOCK_FILES = init_mock_env.c
UTIL_FILES = linked_list.c utils_env.c clean.c error.c utils_exec.c lexel_utils.c
INIT_FILES = init_env_list.c init_env.c
SIGNAL_FILES = signals.c signals_heredoc.c

LIBFT = $(SLIB_DIR)/libft.a

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
	   $(addprefix $(SRC_DIR)/$(INST_DIR)/, $(INST_FILES)) \
	   $(addprefix $(SRC_DIR)/$(FRONT_DIR)/, $(FRONT_FILES)) \
       $(addprefix $(SRC_DIR)/$(BUILTIN_DIR)/, $(BUILTIN_FILES)) \
	   $(addprefix $(SRC_DIR)/$(EXEC_DIR)/, $(EXEC_FILES)) \
	   $(addprefix $(SRC_DIR)/$(MOCK_DIR)/, $(MOCK_FILES)) \
	   $(addprefix $(SRC_DIR)/$(UTILS_DIR)/, $(UTIL_FILES))	\
	   $(addprefix $(SRC_DIR)/$(INIT_DIR)/, $(INIT_FILES))	\
	   $(addprefix $(SRC_DIR)/$(SIGNAL_DIR)/, $(SIGNAL_FILES))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER = $(INCLUDE_DIR)/minishell.h

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -pthread
IFLAGS = -I $(INCLUDE_DIR)
RM = rm -rf

all: $(EXEC)

$(EXEC): $(LIBFT) $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(EXEC)
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

valgrind: $(NAME)
	@echo "\033[1;36m[VALGRIND]\033[0m Executando análise de memória...\n"
	valgrind --suppressions=readline.sup --track-fds=yes \
		--leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re valgrind
