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

	tmp = join(NULL, get_in(shell->line, x));
	y = next_kote(tmp, '$', 0);
	if (y >= 0)
		tmp = join(NULL, dollary(tmp, shell, y));
	while (shell->line[x] != '\0' && str_c(shell->instr, shell->line[x]) < 2)
		x++;
	shell->line = join(NULL, cut_in(shell->line, x));
	shell->type = TXT;
	return (tmp);
}
