/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:03:05 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 05:03:08 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*do_end_nxt(t_mimi *shell, char *tmp, char *str)
{
	if (shell->size == 0)
	{
		shell->line = NULL;
		return (tmp);
	}
	if (shell->line == NULL || !str)
		return (tmp);
	shell->line = NULL;
	return (tmp);
}

char	*do_end_lst(t_mimi *shell, char *tmp, char *str)
{
	shell->line = NULL;
	if (tmp != NULL)
		return (tmp);
	free(tmp);
	return (str);
}

char	*do_end(t_mimi *shell)
{
	char	*str;
	char	*tmp;
	int		x;

	x = 0;
	tmp = NULL;
	str = shell->line;
	while (str && str[x] != '\0')
	{
		if (str[x] == '$')
		{
			tmp = join(tmp, dollary(str, shell, x));
		//	printf("DO_END tmp = %s\n", tmp);
			return (do_end_nxt(shell, tmp, str));
		}
		else
		{
			tmp = join(tmp, cpy_from_two_pos(str, 0, x + 1));
			str = cut_from_pos(str, x + 1);
		}
		x = 0;
	}
	return (do_end_lst(shell, tmp, str));
}
