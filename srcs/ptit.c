/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 08:23:11 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 08:23:14 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
/*
void	ptit_bidule(t_mimi *shell, int x)
{
	shell->tmp = joi(shell->tmp, cftp(shell, 0, x - 1));
	shell->tmp = joi(shell->tmp, ft_itoaa(g_ret));
	shell->t = re_ptit_bidule(shell, 1);
	return ;
}

char	*re_ptit_bidule(t_mimi *shell, int x)
{
	char	*copy;

	copy = ft_strdup(shell->t);
	free(shell->t);
	shell->t = cut_i(copy, x);
	free(copy);
	shell->s = 1;
	if (shell->t == NULL)
	{
		shell->fre = 1;
		if (shell->same == 1)
			shell->line = NULL;
	}
	return (shell->t);
}

void	ptit_free(t_mimi *shell)
{
	if (shell->line && shell->same == 1)
		free(shell->line);
	shell->line = NULL;
}

char	*dol_fin(t_mimi *shell)
{
	if (shell->same != 1)
		shell->size = shell->size - ft_strlenn(shell->t);
	if (shell->fre != 1)
	{
		free(shell->t);
		shell->fre = 1;
		if (shell->same == 1)
			shell->line = NULL;
	}
	return (shell->tmp);
}

char	*ptit_bout_d_free(t_mimi *shell, int x, int y)
{
	char	*copy;

	if (shell->fre != 1)
	{
		copy = ft_strdup(shell->t);
		free(shell->t);
		shell->t = cut_i(copy, x + y);
		free(copy);
		if (shell->t == NULL)
		{
			shell->fre = 1;
			shell->t = NULL;
			if (shell->same == 1)
				shell->line = NULL;
		}
	}
	if (shell->fre != 1 && shell->t == NULL && shell->same == 1)
		ptit_free(shell);
	return (shell->t);
}*/
