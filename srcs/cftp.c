/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cftp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:33:10 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 00:22:45 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*cftp(t_mimi *shell, int s, int e)
{
	char	*tmp;
	int		x;

	x = 0;
	if (shell->t == NULL || s == e)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * ((e - s) + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	while (s < e)
		tmp[x++] = shell->t[s++];
	tmp[x] = '\0';
	return (tmp);
}
