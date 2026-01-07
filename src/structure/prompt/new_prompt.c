/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:22:45 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 11:11:40 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	*new_prompt(void)
{
	t_prompt	*prompt;

	prompt = ft_calloc(1, sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	build_user_pmt(&prompt->user);
	build_host_pmt(&prompt->host);
	build_home_pmt(&prompt->home);
	build_dir_pmt(prompt->home, &prompt->dir);
	build_type_pmt(prompt->user, &prompt->type);
	return (prompt);
}
