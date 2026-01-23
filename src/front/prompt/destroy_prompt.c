/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 11:20:58 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/21 18:56:17 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_prompt(void *ptr)
{
	t_prompt	*prompt;

	if (!ptr)
		return ;
	prompt = (t_prompt *)ptr;
	free(prompt->user);
	free(prompt->host);
	free(prompt->dir);
	free(prompt->utype);
}
