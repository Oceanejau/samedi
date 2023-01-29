/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:58:05 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 07:46:06 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_list	*ft_lstnew(char *content)
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
	if (!newblock->str)
		return ((t_list *)char_err("failed to allocate memory", 2));
	ft_memcpy(newblock->str, content, size);
	newblock->next = NULL;
	return (newblock);
}
