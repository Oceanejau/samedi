/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:48:15 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 05:07:11 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*goty(t_mimi *shell, char *msg, int ret, char c)
{
	free(shell->line);
	shell->line = NULL;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("-\n", 2);
	g_ret = ret;
	return (NULL);
}

char	*next_goats(t_mimi *shell, char *tmp, int x)
{
	int	is;
	is = next_kote(shell->line, '$', 0);
	printf("line = %s, tmp = %s, x = %d, is = %d\n", shell->line, tmp, x, is);
	if (is < x && is != -1)
		tmp = join(tmp, dollary(cpy_from_two_pos(shell->line, 0, x), shell, 0));
	else
		tmp = join(tmp, cpy_from_two_pos(shell->line, 0, x));
	shell->line = join(NULL, cut_in(shell->line, x));
	return (tmp);
}

char	*top_goats(t_mimi *shell, char *tmp, int c_pos)
{
	int		x;
	char	c;

	x = c_pos;
	c = shell->line[c_pos];//reduire lignes
	shell->c = c;//reduire lignes
	x = next_kote(shell->line, shell->line[x], x + 1);
	printf("top goast line = %s, tmp = %s, x = %d, cpos = %d, c = %c\n", shell->line, tmp, x, c_pos, c);
	if (x == -1)
		return (goty(shell, "missing kote -", 2, c));
	else if (c == 34)
		tmp = inside_kote_34(tmp, shell, x, c_pos);
	else
		tmp = inside_kote_39(tmp, shell, x, c_pos);
	return (tmp);
}

char	*goats(t_mimi *shell, int x)
{
	char	*tmp;
	int		c_pos;

	c_pos = -1;
	tmp = NULL;
	x = 0;
	while (shell->line != NULL && shell->line[x] != '\0'
		&& str_c(shell->instr, shell->line[x]) >= 2)
	{
		if (c_pos < 0 && (shell->line[x] == 34 || shell->line[x] == 39))
		{
			c_pos = x;
			tmp = top_goats(shell, tmp, c_pos);
			c_pos = -1;
			x = -1;
		}
		x++;
	}
	if (c_pos == -1 && shell->line)
		tmp = next_goats(shell, tmp, x);
	else if (c_pos != -1)
		return (goty(shell, "missing kote -", 2, shell->c));
	return (tmp);
}
