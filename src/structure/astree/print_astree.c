/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_astree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:10:46 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:30:23 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ast_branch(t_tnode *cursor, int fd, size_t depth);
static void	print_ast_depth(int fd, size_t depth);

void	print_astree(void *ptr, int fd)
{
	t_astree	*astree;

	if (!ptr)
		return ;
	astree = (t_astree *)ptr;
	if (astree->mstype != ASTREE_T)
		return ;
	print_ast_branch(astree->root, fd, 0);
}

static void	print_ast_branch(t_tnode *cursor, int fd, size_t depth)
{
	if (!cursor)
		return ;
	print_ast_depth(fd, depth);
	if (cursor->branch && cursor->branch->left == cursor)
		ft_putstr_fd("├[left] ", fd);
	else if (cursor->branch)
		ft_putstr_fd("└[right] ", fd);
	else
		ft_putstr_fd("┌[root] ", fd);
	if (cursor->data)
		cursor->print(cursor->data, fd);
	ft_putstr_fd("\n", fd);
	print_ast_branch(cursor->left, fd, depth + 1);
	print_ast_branch(cursor->right, fd, depth + 1);
	if (cursor->branch && cursor->branch->type == SUBSHELL)
	{
		print_ast_depth(fd, depth);
		ft_putstr_fd("└[right] empty\n", fd);
	}
}

static void	print_ast_depth(int fd, size_t depth)
{
	size_t	i;

	i = 1;
	while (i < depth)
	{
		ft_putstr_fd("│\t", fd);
		i++;
	}
}
