# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 16:23:40 by mhidani           #+#    #+#              #
#    Updated: 2026/01/23 22:22:17 by mhidani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRC_DIR			= src
OBJ_DIR			= obj
BIN_DIR			= bin
INIT_DIR		= init
SLIB_DIR		= lib
STRUC_DIR		= structure
ASTRE_DIR		= astree
TNODE_DIR		= tnode
LEXTK_DIR		= lextoken
REDIR_DIR		= redirection
COMMD_DIR		= command
STRIN_DIR		= string
SHELL_DIR		= shell
FRONT_DIR		= front
PROMP_DIR		= prompt
LEXER_DIR		= lexer
SYNTX_DIR		= syntax
PARSR_DIR		= parser
EXPAN_DIR		= expand
WILDC_DIR		= wildcard
EXEC_DIR		= exec
BUILTIN_DIR		= builtin
LIBFT_DIR		= libft
INCLUDE_DIR		= include
UTILS_DIR 		= utils
MOCK_DIR		= mock
SIGNAL_DIR		= signals
HEREDOC_DIR		= heredoc
EXEC			= $(BIN_DIR)/$(NAME)

SD_FRONT_DIR	= $(SRC_DIR)/$(FRONT_DIR)
SD_PROMP_DIR	= $(SRC_DIR)/$(FRONT_DIR)/$(PROMP_DIR)
SD_LEXER_DIR	= $(SRC_DIR)/$(FRONT_DIR)/$(LEXER_DIR)
SD_SYNTX_DIR	= $(SRC_DIR)/$(FRONT_DIR)/$(SYNTX_DIR)
SD_PARSR_DIR	= $(SRC_DIR)/$(FRONT_DIR)/$(PARSR_DIR)
SD_EXPAN_DIR	= $(SRC_DIR)/$(FRONT_DIR)/$(EXPAN_DIR)
SD_WILDC_DIR	= $(SRC_DIR)/$(FRONT_DIR)/$(WILDC_DIR)
SD_ASTRE_DIR	= $(SRC_DIR)/$(STRUC_DIR)/$(ASTRE_DIR)
SD_TNODE_DIR	= $(SRC_DIR)/$(STRUC_DIR)/$(TNODE_DIR)
SD_LEXTK_DIR	= $(SRC_DIR)/$(STRUC_DIR)/$(LEXTK_DIR)
SD_REDIR_DIR	= $(SRC_DIR)/$(STRUC_DIR)/$(REDIR_DIR)
SD_COMMD_DIR	= $(SRC_DIR)/$(STRUC_DIR)/$(COMMD_DIR)
SD_STRIN_DIR	= $(SRC_DIR)/$(STRUC_DIR)/$(STRIN_DIR)
SD_SHELL_DIR	= $(SRC_DIR)/$(STRUC_DIR)/$(SHELL_DIR)
SD_BUILT_DIR	= $(SRC_DIR)/$(BUILTIN_DIR)
SD_EXECT_DIR	= $(SRC_DIR)/$(EXEC_DIR)
SD_UTILS_DIR	= $(SRC_DIR)/$(UTILS_DIR)
SD_INIT__DIR	= $(SRC_DIR)/$(INIT_DIR)
SB_SIGNL_DIR	= $(SRC_DIR)/$(SIGNAL_DIR)
SB_HERED_DIR	= $(SRC_DIR)/$(HEREDOC_DIR)

SRC_FILES		= main.c start_minishell.c
SHELL_FILES		= init_shell.c
FRONT_FILES		= handle_input.c
PROMP_FILES		= solve_prompt.c build_prompt.c destroy_prompt.c
LEXER_FILES		= lexer.c config_lexer.c lex_is_jump.c
SYNTX_FILES		= syntax_analyze.c syntax_check.c syntax_check_redir.c \
				  syntax_error_msg.c
PARSR_FILES		= parse_command.c parse_and_or.c parse_pipeline.c parser.c \
				  parse_redir.c parse_subshell.c
EXPAN_FILES		= expand.c handle_expand.c minilex_expand.c \
				  sanitize_quotes.c assignment.c
WILDC_FILES		= wildcard.c expand_args_at.c match_wildcard.c
ASTRE_FILES		= destroy_astree.c get_entry_astree.c new_astree.c \
				  print_astree.c
TNODE_FILES		= destroy_tnode.c new_tnode.c
LEXTK_FILES		= destroy_lextoken.c get_lextoken.c new_lextoken.c \
				  next_lextoken.c
REDIR_FILES		= destroy_lst_redir.c destroy_redir.c new_redir.c
COMMD_FILES		= destroy_cmd.c get_cmd.c new_cmd.c print_cmd.c set_arg_cmd.c
STRIN_FILES		= destroy_cmtx.c print_string.c
BUILTIN_FILES	= builtin.c builtin_echo.c builtin_pwd.c builtin_env.c \
				  builtin_export.c builtin_unset.c builtin_exit.c \
				  builtin_cd.c
EXEC_FILES	  	= executor.c redirect.c execute_external.c execute_ast.c  \
				  execute_pipeline.c
HEREDOC_FILES	= heredoc.c heredoc_fds.c heredoc_prepare.c heredoc_redirect.c
UTIL_FILES		= linked_list.c utils_env.c clean.c error.c utils_exec.c \
				  dlist.c get_names_crrdir.c
INIT_FILES		= init_env_list.c init_env.c
SIGNAL_FILES	= signals.c signals_heredoc.c

LIBFT			= $(SLIB_DIR)/libft.a

SRCS			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))			\
				  $(addprefix $(SD_SHELL_DIR)/, $(SHELL_FILES))		\
				  $(addprefix $(SD_FRONT_DIR)/, $(FRONT_FILES))		\
				  $(addprefix $(SD_ASTRE_DIR)/, $(ASTRE_FILES))		\
				  $(addprefix $(SD_TNODE_DIR)/, $(TNODE_FILES))		\
				  $(addprefix $(SD_LEXTK_DIR)/, $(LEXTK_FILES))		\
				  $(addprefix $(SD_REDIR_DIR)/, $(REDIR_FILES))		\
				  $(addprefix $(SD_COMMD_DIR)/, $(COMMD_FILES))		\
				  $(addprefix $(SD_STRIN_DIR)/, $(STRIN_FILES))		\
	   			  $(addprefix $(SD_PROMP_DIR)/, $(PROMP_FILES))		\
				  $(addprefix $(SD_LEXER_DIR)/, $(LEXER_FILES))		\
				  $(addprefix $(SD_SYNTX_DIR)/, $(SYNTX_FILES))		\
				  $(addprefix $(SD_PARSR_DIR)/, $(PARSR_FILES))		\
				  $(addprefix $(SD_EXPAN_DIR)/, $(EXPAN_FILES))		\
				  $(addprefix $(SD_WILDC_DIR)/, $(WILDC_FILES))		\
       			  $(addprefix $(SD_BUILT_DIR)/, $(BUILTIN_FILES))	\
	   			  $(addprefix $(SD_EXECT_DIR)/, $(EXEC_FILES))		\
	   			  $(addprefix $(SD_UTILS_DIR)/, $(UTIL_FILES))		\
	   			  $(addprefix $(SD_INIT__DIR)/, $(INIT_FILES))		\
	   			  $(addprefix $(SB_SIGNL_DIR)/, $(SIGNAL_FILES))	\
				  $(addprefix $(SB_HERED_DIR)/, $(HEREDOC_FILES))


OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER			= $(INCLUDE_DIR)/minishell.h

CC				= cc
CFLAGS			= -g -Wall -Wextra -Werror -pthread
IFLAGS			= -I $(INCLUDE_DIR)
RM				= rm -rf

all: $(EXEC)

$(EXEC): $(LIBFT) $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(EXEC)
	@echo "[\033[0;32mOK\033[0m] $(NAME) compiled in $(BIN_DIR) 👌👌😍"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "[\033[0;32mOK\033[0m] Compiled: $< ✅"

$(LIBFT):
	@make -C $(SRC_DIR)/$(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[\033[0;31mOK\033[0m] Cleaned object files."

fclean: clean
	@$(RM) $(BIN_DIR)
	@$(RM) $(SLIB_DIR)
	@echo "[\033[0;31mOK\033[0m] Complete cleaning."

re: fclean all

valgrind: $(EXEC)
	@echo "\033[1;36m[VALGRIND]\033[0m Running memory analysis...\n"
	valgrind -s --suppressions=readline.supp --track-fds=yes \
		--leak-check=full --show-leak-kinds=all ./$(EXEC)

.PHONY: all clean fclean re valgrind
