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

t_list	*ft_listnew(char *content, int x)
{
	t_list			*newblock;
	unsigned int	size;

	newblock = (t_list *)malloc(sizeof(*newblock));
	if (!newblock)
		return ((t_list *)char_err("failed to allocate memory", 2));
	if (content == NULL)
	{
		newblock->str = NULL;
		newblock->next = NULL;
		return (newblock);
	}
	size = ft_memlen(content);
	newblock->str = (char *)malloc(sizeof(char) * size + 1);
	newblock->type = x;
	if (!newblock->str)
		return ((t_list *)char_err("failed to allocate memory", 2));
	ft_memcpy(newblock->str, content, size);
	newblock->next = NULL;
	return (newblock);
}

void	ft_listadd_back(t_list **alst, t_list *new)
{
	t_list	*blist;

	if (alst && new)
	{
		blist = (*alst);
		if (blist == NULL)
			(*alst = new);
		else
		{
			while (blist->next)
				blist = blist->next;
			blist->next = new;
		}
	}
}
