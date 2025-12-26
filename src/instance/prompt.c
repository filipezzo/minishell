/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 11:20:58 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/26 11:29:12 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	*new_prompt(void)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	build_user_pmt(&prompt->user);
	build_host_pmt(&prompt->host);
	build_home_pmt(&prompt->home);
	build_dir_pmt(prompt->home, &prompt->dir);
	build_type_pmt(prompt->user, &prompt->type);
	return (prompt);
}

void	destroy_prompt(void *ptr)
{
	t_prompt	*prompt;

	if (!ptr)
		return ;
	prompt = (t_prompt *)ptr;
	free(prompt->user);
	free(prompt->host);
	free(prompt->home);
	free(prompt->dir);
	free(prompt->type);
	free(prompt);
}
