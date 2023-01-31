/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:57:00 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:57:11 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "minishell.h"

char	*cut_i(char *str, int x)
{
	int		y;
	char	*tmp;

	y = 0;
	if (str[0] == '\0')
		return (NULL);
	if ((int)ft_strlenn(str) <= x)
		return (NULL);
	while (str[x + y] != '\0')
		y++;
	if (y == 0 && str)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (y + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	y = 0;
	while (str[x + y] != '\0')
	{
		tmp[y] = str[x + y];
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}
