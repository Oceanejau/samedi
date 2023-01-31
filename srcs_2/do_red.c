/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:25:24 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 07:44:38 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*do_red_next(t_mimi *shell, char *tmp, int x, char c)
{
	shell->retnex = 2;
	if (((shell->line[0] != '\0' && shell->line[1] == '\0' && (shell->line[0]
					!= '<' && c != '>')) || ((shell->line[0] == '>'
					|| shell->line[0] == '<') && (c == '>' || c == '<')
				&& shell->line[1] == '\0' && shell->line[0] == c)))
		return (nexty(shell, "syntax error near unexpected token `newline'"
				, tmp));
	else if (shell->line[0] != c)
		return (nexy(shell, "syntax error near unexpected token `", c, tmp));
	else if (shell->line[0] != '\0' && shell->line[0] == c && (shell->line[1]
			== '>' || shell->line[1] == '<') && (shell->line[2] == '>'
			|| shell->line[2] == '<'))
		return (neyy(shell, "syntax error near unexpected token `", c));
	else if (shell->line[0] != '\0' && shell->line[0] == c && (shell->line[1]
			== '>' || shell->line[1] == '<'))
		return (nexy(shell, "syntax error near unexpected token `", c, tmp));
	else
	{
		tmp = johnny(tmp, get_in(shell->line, x));
		shell->line = cut_in(shell->line, x);
		if (tmp[0] == '<' && tmp[1] == '<')
			shell->nb_hd++;
	}
	return (tmp);
}

char	*do_red(t_mimi *shell, int x, char c)
{
	char	*tmp;

	if (x > 0)
	{
		tmp = get_in(shell->line, x);
		shell->line = cut_in(shell->line, x);
		shell->type = TXT;
		return (tmp);
	}
	if (x == 0)
		x++;
	tmp = get_in(shell->line, x);
	shell->line = cut_in(shell->line, x);
	if (shell->line == NULL)
		return (nexty(shell, "syntax error near unexpected token `newline'"
				, tmp));
	if (shell->line && (shell->line[0] == '<' || shell->line[0] == '>'))
	{
		shell->type = REDIR;
		tmp = do_red_next(shell, tmp, x, c);
	}
	shell->type = REDIR;
	return (tmp);
}
