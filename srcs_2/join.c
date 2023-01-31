/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:54:20 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:55:55 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*join_s(char *s1, char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
	{
		if (s1)
			free(s1);
		return (s2);
	}
	else if (s2 == NULL)
	{
		free(s2);
		return (s1);
	}
	return (NULL);
}

char	*join(char *s1, char *s2)
{
	char	*tmp;
	int		x;
	int		y;

	x = -1;
	tmp = (char *)malloc(sizeof(char) * ((int)ft_strlenn(s1)
				+ (int)ft_strlenn(s2) + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	while (s1[++x] != '\0')
		tmp[x] = s1[x];
	y = 0;
	while (s2[y] != '\0')
		tmp[x++] = s2[y++];
	tmp[x] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (tmp);
}
