/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:37:22 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/13 16:41:30 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define TRUE 0x01
# define FALSE 0x00

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <unistd.h>
# include <stdlib.h>

typedef char	t_bool;

// Data Structures =============================================================
// Doubly Linked List ----------------------------------------------------------
typedef struct s_dlist
{
	struct s_bnode	*head;
	struct s_bnode	*tail;
	size_t			size;
}					t_dlist;
// ---------------------------------------------------------- Doubly Linked List 

// Bidirectional Node ----------------------------------------------------------
typedef struct	s_bnode
{
	void			*data;
	struct s_bnode	*next;
	struct s_bnode	*prev;
	struct s_dlist	*structure;
	t_bool			(*destroy_data)(void *);
}					t_bnode;
// ---------------------------------------------------------- Bidirectional Node
// ============================================================= Data Structures

// Special Generic Functions ===================================================
typedef t_bool	(*destructor)(void *data);
typedef t_bool	(*foreach_callback)(void *crr, void *tgt);
// =================================================== Special Generic Functions

/* Check and Manipulate character ------------------------------------------ */
t_bool	ft_isalpha(int c);
t_bool	ft_isdigit(int c);
t_bool	ft_isalnum(int c);
t_bool	ft_isascii(int c);
t_bool	ft_isprint(int c);
t_bool	ft_isspace(int c);
t_bool	ft_toupper(int c);
t_bool	ft_tolower(int c);

/* Manipulate Strings ------------------------------------------------------ */
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t	ft_strlcat(char *dst, const char *src, size_t dsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strmapi(char const *s, char (*ds)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* Manipulate Memory ------------------------------------------------------- */
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);

/* Numbers ----------------------------------------------------------------- */
int		ft_atoi(const char *src);
long	ft_atol(char *src);
char	*ft_itoa(int n);

/* Write And Read to a File Descriptor ------------------------------------- */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_get_next_line(int fd);

// Data Structures Functions ===================================================
// Doubly Linked List ----------------------------------------------------------

t_dlist	*ft_new_dlist(void);
t_bool	ft_destroy_dlist(void *ptr);
t_dlist	*ft_add_nd_dlist(t_dlist *list, void *data, destructor dst);
t_dlist	*ft_remove_nd_dlist(t_dlist *list, t_bnode *tgt);
t_bnode	*ft_findin_dlist(t_dlist *list, void *data, t_bool (*eq)());
t_bool	ft_foreach_dlist(t_dlist *list, void *data, foreach_callback callback);

// ---------------------------------------------------------- Doubly Linked List

// Birectional Node ------------------------------------------------------------

t_bnode	*ft_new_bnode(void *data, void *structure, destructor dst);
t_bool	ft_setdir_bnode(t_bnode *node, t_bnode *next, t_bnode *prev);
t_bool	ft_destroy_bnode(void *ptr);

// ---------------------------------------------------------- Bidirectional Node
// =================================================== Data Structures Functions

#endif