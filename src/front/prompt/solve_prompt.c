/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:41:45 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/21 19:07:22 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_current_dir(char buffer[]);

char	*build_prompt_user(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		return (ft_strdup("unknown"));
	return (ft_strdup(user));
}

char	*build_prompt_host(void)
{
	int		fd;
	char	buffer[256];
	char	*breakline;
	char	*dot;
	ssize_t	bread;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("unknown"));
	ft_memset(buffer, 0, 256);
	bread = read(fd, buffer, 255);
	if (bread < 0)
		return (ft_strdup("unknown"));
	close(fd);
	breakline = ft_strchr(buffer, '\n');
	if (breakline)
		ft_memset(breakline, 0, breakline - buffer);
	dot = ft_strchr(buffer, '.');
	if (dot)
		ft_memset(dot, 0, dot - buffer);
	return (ft_strdup(buffer));
}

char	*build_prompt_dir(void)
{
	char	buffer[PATH_MAX];
	char	*home;
	char	*target;
	size_t	hlen;
	size_t	clen;

	get_current_dir(buffer);
	home = getenv("HOME");
	if (home)
	{
		hlen = ft_strlen(home);
		clen = ft_strlen(buffer);
		target = ft_strnstr(buffer, home, hlen);
		if (target)
		{
			ft_memmove(buffer + 1, buffer + hlen, clen - hlen);
			ft_memset(buffer + clen - hlen + 1, 0, clen + hlen + 1);
			buffer[0] = '~';
			return (ft_strdup(buffer));
		}
	}
	return (ft_strdup(home));
}

char	*build_prompt_utype(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		return (ft_strdup("?"));
	if (user && ft_strncmp(user, "root", 4) != 0)
		return (ft_strdup("$"));
	return (ft_strdup("#"));
}

static void	get_current_dir(char buffer[])
{
	if (!getcwd(buffer, PATH_MAX))
	{
		buffer[0] = '?';
		ft_memset(buffer + 1, 0, PATH_MAX - 1);
	}
}
