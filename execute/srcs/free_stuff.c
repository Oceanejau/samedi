/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:10:22 by wmari             #+#    #+#             */
/*   Updated: 2023/02/07 19:33:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	free_block(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
			free(block[i][j++]);
		free(block[i][j]);
		free(block[i++]);
	}
	free(block[i]);
	free(block);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
}

void	free_list(t_mimi *shell)
{
	if (shell->list)
		free_listrec(shell->list);
	shell->list = NULL;
}

void	free_env(t_mimi *shell)
{
	if (shell->envlist)
		free_listrec(shell->envlist);
	shell->envlist = NULL;
}

void	free_listrec(t_list *list)
{
	if (list->next)
		free_listrec(list->next);
	free(list->str);
	free(list);
}
