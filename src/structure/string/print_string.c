/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:45:49 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 15:29:10 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_string(void *ptr, int fd)
{
	char	*string;

	if (!ptr || fd < 0)
		return ;
	string = (char *)ptr;
	ft_putstr_fd(string, fd);
}
