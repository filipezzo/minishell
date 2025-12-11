
NAME		= libft
VERSION		= 1.0

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar
ARFLAGS		= -rcs

OBJ_DIR		= ../../obj/libft
INC_DIR		= ../../include
SLIB_DIR	= ../../lib

SRCS		= \
			ft_add_nd_dlist.c ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c \
			ft_destroy_bnode.c ft_destroy_dlist.c ft_findin_bnode.c \
			ft_foreach_dlist.c ft_get_next_line.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_new_bnode.c ft_new_dlist.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_remove_nd_dlist.c \
			ft_setdir_bnode.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			ft_substr.c ft_tolower.c ft_toupper.c
OBJS		= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
SLIB		= $(SLIB_DIR)/$(NAME).a

GREEN		:= \033[0;32m
RED			:= \033[0;31m
RESET		:= \033[0m

all: $(SLIB)

$(SLIB): $(OBJS) | $(SLIB_DIR)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "[$(GREEN)OK$(RESET)] Static Libft library generated"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "[$(GREEN)OK$(RESET)] Compiled: $<"

print:
	@echo $(OBJS)

$(OBJ_DIR):
	@mkdir -p $@

$(SLIB_DIR):
	@mkdir -p $@

clean:
	@rm -f $(OBJS)
	@echo "[$(RED)OK$(RESET)] Libft object files cleaned"

fclean: clean
	@rm -f $(SLIB)
	@echo "[$(RED)OK$(RESET)] Libft static lib file cleaned"

re: fclean all

.PHONY: clean fclean all re