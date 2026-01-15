/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:01:03 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:10:02 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool	handle_pstring(int fd, va_list args, ssize_t *count);

ssize_t	ft_fputstr_fd(int fd, char *src, ...)
{
	va_list	args;
	ssize_t	count;

	if (fd < 0 || !src)
		return (-1);
	count = 0;
	va_start(args, src);
	while (*src)
	{
		if (ft_strncmp(src, "%s", 2) == 0)
		{
			if (!handle_pstring(fd, args, &count))
				return (va_end(args), -1);
			src += 2;
			continue ;
		}
		count += write(fd, src, 1);
		src++;
	}
	va_end(args);
	return (count);
}

static t_bool	handle_pstring(int fd, va_list args, ssize_t *count)
{
	char	*str;

	if (fd < 0 || !args || *count < 0)
		return (FALSE);
	str = va_arg(args, char *);
	if (!str)
	{
		*count += write(fd, "(null)", 6);
		return (TRUE);
	}
	while (*str)
		*count += write(fd, str++, 1);
	return (TRUE);
}
