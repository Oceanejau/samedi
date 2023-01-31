/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_of_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:48:20 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:48:55 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*piece_of_string(char *str, int deb, int fin)
{
	char	*tmp;
	int		x;

	x = 0;
	tmp = (char *)malloc(sizeof(char) * (fin - deb + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	while (deb + x < fin)
	{
		tmp[x] = str[deb + x];
		x++;
	}
	tmp[x] = '\0';
	return (tmp);
}
