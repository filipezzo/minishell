NAME			  = minishell

SRC_DIR			  = src
OBJ_DIR			  = obj
BIN_DIR			  = bin
INIT_DIR		  = init
SLIB_DIR		  = lib
STRUC_DIR		  = structure
FRONT_DIR		  = front
EXEC_DIR		  = exec
BUILTIN_DIR		  = builtin
LIBFT_DIR		  = libft
INCLUDE_DIR		  = include
UTILS_DIR 		  = utils
MOCK_DIR		  = mock
SIGNAL_DIR		  = signals

EXEC			  = $(BIN_DIR)/$(NAME)

SRC_FILES		  = main.c

FRONT_READL_FILES = readline/build_dir_pmt.c readline/build_home_pmt.c \
					readline/build_host_pmt.c readline/build_prompt.c \
					readline/build_type_pmt.c readline/build_user_pmt.c
FRONT_LEXER_FILES = lexer/lexer.c lexer/config_lexer.c
FRONT_SYNTX_FILES = syntax/syntax_analyze.c syntax/syntax_check.c \
					syntax/syntax_check_redir.c syntax/syntax_error_msg.c
FRONT_PARSR_FILES = parser/parse_command.c parser/parse_and_or.c \
					parser/parse_pipeline.c parser/parser.c \
					parser/parse_redir.c parser/parse_subshell.c
STRUC_ASTRE_FILES = astree/destroy_astree.c astree/get_entry_astree.c \
					astree/new_astree.c astree/print_astree.c
STRUC_TNODE_FILES = tnode/destroy_tnode.c tnode/new_tnode.c
STRUC_LEXTK_FILES = lextoken/destroy_lextoken.c lextoken/get_lextoken.c \
					lextoken/new_lextoken.c lextoken/next_lextoken.c
STRUC_REDIR_FILES = redirection/destroy_lst_redir.c \
					redirection/destroy_redir.c redirection/new_redir.c
STRUC_PROMP_FILES = prompt/destroy_prompt.c prompt/new_prompt.c
STRUC_COMMD_FILES = command/destroy_cmd.c command/get_cmd.c \
					command/new_cmd.c command/print_cmd.c command/set_arg_cmd.c
STRUC_STRIN_FILES = string/destroy_string_lst.c string/print_string.c
BUILTIN_FILES	  = builtin.c builtin_echo.c builtin_pwd.c builtin_env.c \
					builtin_export.c builtin_unset.c builtin_exit.c \
					builtin_cd.c
EXEC_FILES		  = executor.c redirect.c execute_external.c exec_ast.c
MOCK_FILES		  = init_mock_env.c
UTIL_FILES		  = linked_list.c utils_env.c clean.c error.c utils_exec.c \
					lexel_utils.c
INIT_FILES		  = init_env_list.c init_env.c
SIGNAL_FILES	  = signals.c signals_heredoc.c

LIBFT			  = $(SLIB_DIR)/libft.a

SRCS			  = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
					$(addprefix $(SRC_DIR)/$(STRUC_DIR)/, $(STRUC_ASTRE_FILES))\
					$(addprefix $(SRC_DIR)/$(STRUC_DIR)/, $(STRUC_TNODE_FILES))\
					$(addprefix $(SRC_DIR)/$(STRUC_DIR)/, $(STRUC_LEXTK_FILES))\
					$(addprefix $(SRC_DIR)/$(STRUC_DIR)/, $(STRUC_REDIR_FILES))\
					$(addprefix $(SRC_DIR)/$(STRUC_DIR)/, $(STRUC_PROMP_FILES))\
					$(addprefix $(SRC_DIR)/$(STRUC_DIR)/, $(STRUC_COMMD_FILES))\
					$(addprefix $(SRC_DIR)/$(STRUC_DIR)/, $(STRUC_STRIN_FILES))\
	   				$(addprefix $(SRC_DIR)/$(FRONT_DIR)/, $(FRONT_READL_FILES))\
					$(addprefix $(SRC_DIR)/$(FRONT_DIR)/, $(FRONT_LEXER_FILES))\
					$(addprefix $(SRC_DIR)/$(FRONT_DIR)/, $(FRONT_SYNTX_FILES))\
					$(addprefix $(SRC_DIR)/$(FRONT_DIR)/, $(FRONT_PARSR_FILES))\
       				$(addprefix $(SRC_DIR)/$(BUILTIN_DIR)/, $(BUILTIN_FILES)) \
	   				$(addprefix $(SRC_DIR)/$(EXEC_DIR)/, $(EXEC_FILES)) \
	   				$(addprefix $(SRC_DIR)/$(MOCK_DIR)/, $(MOCK_FILES)) \
	   				$(addprefix $(SRC_DIR)/$(UTILS_DIR)/, $(UTIL_FILES)) \
	   				$(addprefix $(SRC_DIR)/$(INIT_DIR)/, $(INIT_FILES))	\
	   				$(addprefix $(SRC_DIR)/$(SIGNAL_DIR)/, $(SIGNAL_FILES))

OBJS			  = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER			  = $(INCLUDE_DIR)/minishell.h

CC				  = cc
CFLAGS			  = -g -Wall -Wextra -Werror -pthread
IFLAGS			  = -I $(INCLUDE_DIR)
RM				  = rm -rf

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

valgrind: $(EXEC)
	@echo "\033[1;36m[VALGRIND]\033[0m Executando análise de memória...\n"
	valgrind -q --suppressions=readline.sup --track-fds=yes \
		--leak-check=full --show-leak-kinds=all ./$(EXEC)

.PHONY: all clean fclean re valgrind
