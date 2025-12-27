/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:19:15 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/27 18:21:01 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	syntax_error_message(char *msg)
{
	ft_fputstr_fd(STDERR_FILENO, "minishell: %s\n", msg);
	return (FALSE);
}
