/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insides.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 07:10:52 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 07:10:55 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*inside_kote_34(char *str, t_mimi *shell, int x, int c_pos)
{
	char	*tmp;
	char	*tmpp;
	int		y;

	tmp = NULL;
	if (c_pos > 0 && shell->line[c_pos - 1] == '$')
		tmp = cpy_from_two_pos(shell->line, 0, c_pos - 1);
	else
		tmp = cpy_from_two_pos(shell->line, 0, c_pos);
	if (str == NULL && shell->line[0] == 34 && shell->line[1] == 34
		&& (str_c(shell->instr, shell->line[2]) < 2 || shell->line[2] == '\0'))
	{
		tmp = join(tmp, malicious("\'\'"));
		shell->type = QUOTE;
	}
	y = next_kote(tmp, '$', 0);
	if (y >= 0)
		tmp = join(NULL, dollary(tmp, shell, next_kote(tmp, '$', 0)));
	tmpp = cpy_from_two_pos(shell->line, c_pos + 1, x);
	shell->line = join(NULL, cut_in(shell->line, x + 1));
	if (next_kote(tmpp, '$', 0) >= 0)
		tmpp = join(NULL, dollary(tmpp, shell, next_kote(tmpp, '$', 0)));
	tmp = join(tmp, tmpp);
	tmp = join(str, tmp);
	return (tmp);
}

char	*inside_kote_39(char *str, t_mimi *shell, int x, int c_pos)
{
	char	*tmp;

	tmp = NULL;
	if (str == NULL && shell->line[0] == 39 && shell->line[1] == 39
		&& (str_c(shell->instr, shell->line[2]) < 2 || shell->line[2] == '\0'))
	{
		tmp = join(tmp, malicious("\'\'"));
		shell->type = QUOTE;
	}
	if (c_pos > 0 && shell->line[c_pos - 1] == '$')
		tmp = join(tmp, cpy_from_two_pos(shell->line, 0, c_pos - 1));
	else
		tmp = join(tmp, cpy_from_two_pos(shell->line, 0, c_pos));
	tmp = join(tmp, cpy_from_two_pos(shell->line, c_pos + 1, x));
	shell->line = join(NULL, cut_in(shell->line, x + 1));
	tmp = join(str, tmp);
	return (tmp);
}
