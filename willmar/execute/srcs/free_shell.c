/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:49:33 by wmari             #+#    #+#             */
/*   Updated: 2023/01/26 21:42:01 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	last_cmd(char ***block, int index, int *fd)
{
	if (block[index + 1] == NULL)
		close(*fd);
}

static void	free_shell_list(t_list	*list)
{
	if (list->next)
		free_shell_list(list->next);
	free(list->str);
	free(list);
}

void	free_list(t_mimi *shell)
{
	if (shell->list)
		free_shell_list(shell->list);
	shell->list = NULL;
}

void	free_env(t_mimi *shell)
{
	if (shell->envlist)
		free_shell_list(shell->envlist);
	shell->envlist = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
