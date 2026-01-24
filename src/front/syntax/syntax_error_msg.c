/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:19:15 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/15 11:42:46 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	syntax_err_msg(char *msg, char *oper)
{
	ft_fputstr_fd(STDERR_FILENO, "minishell: %s '%s'\n", msg, oper);
	return (FALSE);
}

t_bool	syntax_err_smsg(char *msg)
{
	ft_fputstr_fd(STDERR_FILENO, "minishell: %s\n", msg);
	return (FALSE);
}
