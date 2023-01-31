/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 07:19:31 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 07:19:33 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	show_list(t_mimi *shell)
{
	t_list	*new;

	new = shell->list;
	printf("========showlist main========\n");
	while (new != NULL)
	{
		printf("str = -%s- type = %d\n", new->str, new->type);
		new = new->next;
	}
	printf("==========fin list===========\n");
	return ;
}
