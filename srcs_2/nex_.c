/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nex_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 06:41:34 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 06:41:36 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*nexty(t_mimi *shell, char *msg, char *tmp)
{
	free(shell->line);
	free(tmp);
	shell->line = NULL;
	return (char_err(msg, shell->retnex));
}

char	*nexy(t_mimi *shell, char *msg, char c, char *tmp)
{
	free(shell->line);
	free(tmp);
	shell->line = NULL;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_ret = shell->retnex;
	return (NULL);
}

char	*ney(t_mimi *shell, char *msg, int ret, char c)
{
	free(shell->line);
	shell->line = NULL;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_ret = ret;
	return (NULL);
}

char	*neyy(t_mimi *shell, char *msg, char c)
{
	free(shell->line);
	shell->line = NULL;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_ret = shell->retnex;
	return (NULL);
}
