/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malicious.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:49:16 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:50:42 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*malicious(char *str)
{
	char	*tmp;
	int		x;

	x = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	while (str[x] != '\0')
	{
		tmp[x] = str[x];
		x++;
	}
	tmp[x] = '\0';
	return (tmp);
}
