/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:33:04 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:39:47 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*do_pipe(t_mimi *shell, int x)
{
	char	*tmp;
	int		y;

	//printf("DO_PIPE\n");
	if (x == 0)
	{
		tmp = get_in(shell->line, 1);
		shell->line = cut_in(shell->line, 1);
		shell->type = PIPE;
		if (ft_strlen(shell->line) == 0)
			return(nexy(shell, "syntax error near unexpected token `", 2, '|'));
		return (tmp);
	}
	tmp = get_in(shell->line, x);
	y = next_kote(tmp, '$', 0);
	if (y >= 0)
		tmp = dollary(tmp, shell, y);
	shell->line = cut_in(shell->line, x);
	return (tmp);
}
