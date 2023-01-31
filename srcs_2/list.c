/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:50:55 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:51:12 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*blist;

	if (alst && new)
	{
		blist = (*alst);
		if (blist == NULL)
		{
			(*alst = new);
		}
		else
		{
			while (blist->next)
				blist = blist->next;
			blist->next = new;
		}
	}
}
