/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dol_else.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:10:05 by ojauregu          #+#    #+#             */
/*   Updated: 2023/02/07 19:10:08 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	dolly(t_mimi *shell, int x)
{
	char	*copy;

	if (x > 1)
		shell->tmp = joi(shell->tmp, cftp(shell, 0, x - 1));
	copy = ft_strdup(shell->t);
	free(shell->t);
	shell->t = cut_i(copy, x + 1);
	free(copy);
	return ;
}

char	*dol_else(t_mimi *shell, int x)
{
	char	*copy;

	if (shell->fre != 1 && shell->t != NULL)
	{
		shell->tmp = joi(shell->tmp, cftp(shell, 0, x + 1));
		copy = ft_strdup(shell->t);
		free(shell->t);
		shell->t = cut_i(copy, x + 1);
		free(copy);
	}
	else
		return (NULL);
	return (shell->t);
}
