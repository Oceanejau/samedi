/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 06:42:15 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 07:46:36 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	int_err(char *msg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_ret = ret;
	return (ret);
}
