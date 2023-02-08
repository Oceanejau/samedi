/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartiteur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:47:48 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:48:06 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*repartiteur(t_mimi *shell, int x, char *str)
{
	shell->type = TXT;
	if (str_c(shell->instr, shell->line[x]) < 2)
		str = do_white(shell, x);
	else if (str_c(shell->instr, shell->line[x]) < 4)
		str = goats(shell, x);
	else if (str_c(shell->instr, shell->line[x]) == 4)
		str = do_pipe(shell, x);
	else if (str_c(shell->instr, shell->line[x]) < 7)
		str = do_red(shell, x, shell->line[x]);
	else
		str = do_end(shell);
	printf("LINE rep = %s\n", shell->line);
	return (str);
}
