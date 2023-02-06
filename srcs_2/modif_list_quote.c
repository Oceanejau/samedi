/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_list_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:54:03 by ojauregu          #+#    #+#             */
/*   Updated: 2023/02/04 17:57:48 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	modif_list_quote(t_mimi *shell)
{
	t_list	*new;

	new = shell->list;
	while (new != NULL)
	{
		if (new->type == 3)
		{
			free(new->str);
		///////option malloc '\0'/////////
			new->str = (char *)malloc(sizeof(char) * 1);
			if (!new->str)
				return (-1);// free toute la liste
			new->str[0] = '\0';
		/////fin de l'option malloc '\0'/////
		//
		///////option NULL//////
			//new->str = NULL;
		///////fin option NULL///////
		}
		new = new->next;
	}
	return (0);
}
