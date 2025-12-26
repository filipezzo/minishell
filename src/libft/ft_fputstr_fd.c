/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:01:03 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/22 16:30:22 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool	handle_pstring(int fd, va_list args, ssize_t *count);

/**
 * Prints a string that, when the special character `%s` is indicated only once, 
 * will replace it with another string that must be placed in its place.
 * 
 * @param fd Code of the File Descriptor where the string will be printed.
 * @param src String content to be printed, containing or not containing the 
 * special character flags `%s`. When specified, this will indicate where it will
 * be replaced by the character string indicated by the variadic arguments 
 * attribute.
 * @param ... All strings that may be present in the final result when replacing
 * special character `%s` that indicate replacement.
 * @return Total characters printed.
 */
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
