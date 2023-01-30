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


char	*inside_kote_34(char *str, t_mimi *shell, int x, int c_pos)
{
	char	*tmp;
	char	*tmpp;
	int		y;

	tmp = NULL;
	printf("debut 34 str = -%s-,x =  %d, cpos = %d\n", str, x, c_pos);
	if (c_pos > 0 && shell->line[c_pos - 1] == '$')
		tmp = join(tmp, cpy_from_two_pos(shell->line, 0, c_pos - 1));
	else
		tmp = join(tmp, cpy_from_two_pos(shell->line, 0, c_pos));
	y = next_kote(tmp, '$', 0);
	if (y >= 0)
		tmp = join(NULL, dollary(tmp, shell, next_kote(tmp, '$', 0)));
	tmpp = join(NULL, cpy_from_two_pos(shell->line, c_pos + 1, x));
	printf("tmpp = ,%s, %d\n", tmpp, (int)ft_strlen(tmpp));
	shell->line = join(NULL, cut_in(shell->line, x + 1));
	if (next_kote(tmpp, '$', 0) >= 0)
		tmpp = join(NULL, dollary(tmpp, shell, next_kote(tmpp, '$', 0)));
	//printf("TEST1 = tmp = %s, shell = %s, str %s, y = %d, tmpp=%s\n", tmp, shell->line, str, y, tmpp);

	tmp = join(tmp, tmpp);
	tmp = join(str, tmp);

	//printf("TEST2 = tmp = %s, shell = %s, str %s, tmpp = %s\n", tmp, shell->line, str, tmpp);
	return (tmp);
}

char	*inside_kote_39(char *str, t_mimi *shell, int x, int c_pos)
{
	char	*tmp;

	tmp = NULL;
	if (c_pos > 0 && shell->line[c_pos - 1] == '$')
		tmp = join(tmp, cpy_from_two_pos(shell->line, 0, c_pos - 1));
	else
		tmp = join(tmp, cpy_from_two_pos(shell->line, 0, c_pos));
	tmp = join(tmp, cpy_from_two_pos(shell->line, c_pos + 1, x));
	shell->line = join(NULL, cut_in(shell->line, x + 1));
	tmp = join(str, tmp);
	return (tmp);
}

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

char	*goats(t_mimi *shell, int x)
{
	char	*tmp;
	char	c;
	int		c_pos;

	c_pos = -1;
	tmp = NULL;
	x = 0;
	printf("GOATS, %s, %d\n", shell->line, x);
	while (shell->line != NULL && shell->line[x] != '\0' && str_c(shell->instr, shell->line[x]) >= 2)
	{
		if (c_pos < 0 && (shell->line[x] == 34 || shell->line[x] == 39))
		{
			c = shell->line[x];
			c_pos = x;
			x = next_kote(shell->line, shell->line[x], x + 1);
			if (x == -1)
				return (goty(shell, "missing kote -", 2, c));
			else if (c == 34)
				tmp = inside_kote_34(tmp, shell, x, c_pos);
			else
				tmp = inside_kote_39(tmp, shell, x, c_pos);
			c_pos = -1;
			x = -1;
		}
		x++;
	}
	if (c_pos == -1 && shell->line)
	{
		printf("ooijoo %s,%d\n",shell->line, x);
		tmp = join(tmp, dollary(cpy_from_two_pos(shell->line, 0, x), shell, 0));
		shell->line = join(NULL, cut_in(shell->line, x));
		printf("ooijoo %s -%s-,%d\n",shell->line, tmp, x);

	}
	else if (c_pos != -1)
		return (goty(shell, "missing kote -", 2, c));
	printf("tmp = %s, shell->lnie = %s\n", tmp, shell->line);
	return(tmp);
}
