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

void	ret_et_free(char *str, int x, t_mimi *shell, t_list *new)
{
	if (x == 2 && new != NULL)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(new->str, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (x == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("memory\n", 2);
	}
	mani_free(shell, malicious("truc"));
}

void	modif_list_quote(t_mimi *shell)
{
	t_list	*new;

	new = shell->list;
	while (new && new != NULL)
	{
		if (new->type == QUOTE)
		{
			free(new->str);
			new->str = (char *)malloc(sizeof(char) * 1);
			if (!new->str)
				return (ret_et_free("failed to allocate ", 1, shell, new));
			new->str[0] = '\0';
		}
		if (new->type == REDIR)
		{
			new = new->next;
			if (new != NULL && new->type == TXT)
				new->type = NAMEFILE;
			else
				return (ret_et_free(NULL, 2, shell, new));
		}
		else
			new = new->next;
	}
}
