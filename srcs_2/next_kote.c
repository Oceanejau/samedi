/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_kote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:43:45 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:43:48 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	next_kote(char *str, char c, int x)
{
	printf("next kote x = %d\n", x);
	while (str && str[x] != '\0')
	{
		if (str[x] == c)
		{
			printf("x = %d, c = -%c-\n", x, c);
			return (x);
		}
		x++;
	}
	printf("SORT\n");
	return (-1);
}
