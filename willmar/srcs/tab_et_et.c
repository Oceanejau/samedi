/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_et_et.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:55:56 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 07:47:50 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**malloc_char_et_et(int size)
{
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
	{
		char_err("failed to allocate memory", 2);
		return (NULL);
	}
	return (tmp);
}

char	*copy_char_et(char *str)
{
	int		x;
	char	*tmp;

	x = 0;
	while (str[x] != '\0')
		x++;
	tmp = (char *)malloc(sizeof(char) * (x + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	x = 0;
	while (str[x] != '\0')
	{
		tmp[x] = str[x];
		x++;
	}
	tmp[x] = '\0';
	return (tmp);
}

char	**error_copy_char_et_et(char **tmp, int size)
{
	int	y;

	y = 0;
	while (y < size)
	{
		free(tmp[y]);
		y++;
	}
	free(tmp);
	return (NULL);
}

char	**copy_char_et_et(char **str)
{
	char	**tmp;
	int		y;

	y = 0;
	while (str[y] != NULL)
		y++;
	tmp = malloc_char_et_et(y);
	y = 0;
	while (str[y] != NULL)
	{
		tmp[y] = copy_char_et(str[y]);
		if (tmp[y] == NULL)
			return (error_copy_char_et_et(tmp, y));
		y++;
	}
	tmp[y] = NULL;
	return (tmp);
}
