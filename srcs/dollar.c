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

	if (shell->t != NULL)
	{
		shell->tmp = joi(shell->tmp, cpy_from_two_posi(shell, 0, x + 1));
		copy = ft_strdup(shell->t);
		///free(str);//
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
		shell->tmp = ptit_bidule(shell, x);
	else if (shell->t && shell->t[x + y] != '\0' && shell->t[x + y] != '$'
		&& str_c(shell->instr, shell->t[x + y]) == 10)
		return (char_err("something went wrong with this variable", 2));
	else if (y == 0)
		shell->tmp = joi(shell->tmp, malicious("$"));
	shell->tmp = joi(shell->tmp, find_env(cpy_from_two_posi(shell, x, x + y),
				shell));
	return (shell->tmp);
}

char	*doll(t_mimi *shell, int x)
{
	int		y;
	char	*copy;

	y = 0;
	if (ft_is_nb(shell->t[x]) == 1)
	{
		if (x > 1)
			shell->tmp = joi(shell->tmp, cpy_from_two_posi(shell, 0, x - 1));
		copy = ft_strdup(shell->t);
		free(shell->t);
		shell->t = cut_i(copy, x + 1);
		free(copy);
	}
	else if (ft_is_nb(shell->t[x]) != 1)
	{
		while ((ft_is_nb(shell->t[x + y]) == 1 || ft_is_alpha(shell->t[x + y]) == 1
				|| shell->t[x + y] == '_') && shell->t[x + y] != '\0')
			y++;
		shell->tmp = bb_mid(shell, x, y);
	//	printf("TMP sortie = -%s-\n", shell->tmp);
		if (shell->t != NULL && shell->t[x] != '\0' && shell->t[x + 1] == '$')
			shell->t = re_ptit_bidule(shell, x);
		shell->t = ptit_bout_d_free(shell, x, y);
	}
	if (shell->t == NULL)
		shell->fre = 1;
	return (shell->t);
}

char	*dollary(char *str, t_mimi *shell, int x)
{
//	printf("DOLLAR -%s-\n", shell->t);
	shell->tmp = NULL;
	shell->t = str;
	if (shell->t == shell->line)
		shell->same = 1;
	shell->size = ft_strlenn(shell->t);
	shell->s = ft_strlenn(shell->line);
	while (shell->fre != 1 && /*str && ft_strlenn(str) > 0 &&*/ (shell->t[x] && shell->t[x] != '\0'))
	{
		///printf("STR = -%s-, tmp =-%s-\n", shell->t, shell->tmp);
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
