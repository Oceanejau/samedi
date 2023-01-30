
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_white.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:01:46 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 05:01:57 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*do_white(t_mimi *shell, int x)
{
	char	*tmp;
	int		y;

	printf("do_white\n");
	tmp = join(NULL, get_in(shell->line, x));
	printf("tmp = %s\n", tmp);
	y = next_kote(tmp, '$', 0);
	printf("Y = %d\n", y);
	if (y >= 0)
		tmp = join(NULL, dollary(tmp, shell, y));
	while (shell->line != NULL && shell->line[x] != '\0' && str_c(shell->instr, shell->line[x]) < 2)
		x++;
	printf("reend tmp = -%s-, shell->line =-%s-\n", tmp, shell->line);
	shell->line = join(NULL, cut_in(shell->line, x));
	shell->type = TXT;
	printf("whiteeeeee tmp = %s, line = %s\n", tmp, shell->line);
	return (tmp);
}
