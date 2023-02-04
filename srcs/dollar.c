/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 08:23:51 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 08:23:57 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*dol_else(t_mimi *shell, int x)
{
	char	*copy;

	if (shell->fre != 1 && shell->t != NULL)
	{
		shell->tmp = joi(shell->tmp, cpy_from_two_posi(shell, 0, x + 1));
		copy = ft_strdup(shell->t);
		free(shell->t);
		shell->t = cut_i(copy, x + 1);
		free(copy);
	}
	else
		return (NULL);
	return (shell->t);
}

char	*bb_mid(t_mimi *shell, int x, int y)
{
	if (y == 0 && shell->t[x + y] == '?')
	{
		shell->tmp = ptit_bidule(shell, x);
		y++;
	}
	else if (shell->t && shell->t[x + y] != '\0' && shell->t[x + y] != '$'
		&& str_c(shell->instr, shell->t[x + y]) == 10)
		return (char_err("something went wrong with this variable", 2));
	else if (y == 0)
		shell->tmp = joi(shell->tmp, malicious("$"));
	shell->tmp = joi(shell->tmp, find_env(cpy_from_two_posi(shell, x, x + y),
				shell));
	return (shell->tmp);
}

void	dolly(t_mimi *shell, int x)
{
	char	*copy;

	if (x > 1)
		shell->tmp = joi(shell->tmp, cpy_from_two_posi(shell, 0, x - 1));
	copy = ft_strdup(shell->t);
	free(shell->t);
	shell->t = cut_i(copy, x + 1);
	free(copy);
	return ;
}

char	*doll(t_mimi *shell, int x)
{
	int	y;

	y = 0;
	if (ft_is_nb(shell->t[x]) == 1)
		dolly(shell, x);
	else if (ft_is_nb(shell->t[x]) != 1)
	{
		while ((ft_is_nb(shell->t[x + y]) == 1 || ft_is_alpha(shell->t[x + y])
				== 1 || shell->t[x + y] == '_') && shell->t[x + y] != '\0')
			y++;
		shell->tmp = bb_mid(shell, x, y);
		if (shell->vent != 0)
			y = shell->vent;
		else if (shell->t != NULL && shell->t[x] != '\0' && shell->t[x + 1]
			== '$')
			shell->t = re_ptit_bidule(shell, x);
		shell->t = ptit_bout_d_free(shell, x, y);
	}
	if (shell->t == NULL)
		shell->fre = 1;
	return (shell->t);
}

char	*dollary(char *str, t_mimi *shell, int x)
{
	shell->vent = 0;
	shell->tmp = NULL;
	shell->t = str;
	if (shell->t == shell->line)
		shell->same = 1;
	shell->size = ft_strlenn(shell->t);
	shell->s = ft_strlenn(shell->line);
	while (shell->fre != 1 && (shell->t && shell->t[x] != '\0'))
	{
		if (shell->t[x] == '$')
		{
			x++;
			doll(shell, x);
			x = 0;
		}
		else
			dol_else(shell, x);
		x = 0;
	}
	return (dol_fin(shell));
}
