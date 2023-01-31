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

char	*ptit_bidule(t_mimi *shell, char *str, int x)
{
	shell->tmp = joi(shell->tmp, cpy_from_two_posi(str, 0, x - 1));
	shell->tmp = joi(shell->tmp, ft_itoaa(g_ret));
	return (shell->tmp);
}

char	*re_ptit_bidule(char *str, t_mimi *shell, int x)
{
	char	*copy;

	copy = ft_strdup(str);
	free(str);
	str = cut_i(copy, x);
	free(copy);
	shell->s = 1;
	return (str);
}

void	ptit_free(t_mimi *shell)
{
	free(shell->line);
	shell->line = NULL;
}

char	*dol_fin(t_mimi *shell, char *str)
{
	shell->size = shell->size - ft_strlenn(str);
	free(str);
	return (shell->tmp);
}

char	*ptit_bout_d_free(t_mimi *shell, char *str, int x, int y)
{
	char	*copy;

	copy = ft_strdup(str);
	free(str);
	str = cut_i(copy, x + y);
	free(copy);
	if (str == NULL && shell->size == shell->s)
		ptit_free(shell);
	return (str);
}
