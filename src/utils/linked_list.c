/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:47:58 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/18 17:48:03 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list_elements(t_env *list)
{
	int count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}

	return (count);
}
