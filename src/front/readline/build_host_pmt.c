/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_host_pmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:02:05 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/26 11:23:39 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_and_build(char **crr);

char	*build_host_pmt(char **crr)
{
	int		fd;
	char	*bkline_pvt;
	char	buffer[256];
	ssize_t	bread;

	if (*crr && ft_strncmp(*crr, "unknown", 7) != 0)
		return (*crr);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (check_and_build(crr));
	bread = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bread <= 0)
		return (check_and_build(crr));
	bkline_pvt = ft_strchr(buffer, '\n');
	ft_memset(bkline_pvt, '\0', bkline_pvt - buffer);
	buffer[bread] = '\0';
	free(*crr);
	*crr = ft_strdup(buffer);
	return (*crr);
}

static char	*check_and_build(char **crr)
{
	if (*crr && ft_strncmp(*crr, "unknown", 7) == 0)
		return (*crr);
	free(*crr);
	*crr = ft_strdup("unknown");
	return (*crr);
}
