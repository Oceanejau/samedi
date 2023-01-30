/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_from_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:03:53 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 05:04:02 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*cut_from_pos(char *str, int e)
{
	char	*tmp;
	int		x;

/*ft_putstr_fd("str :", 2);
ft_putstr_fd(str, 2);
ft_putstr_fd("\n", 2);

exit (0);*/
	if (str == NULL/* || e >= (int)ft_strlen(str)*/)
	{
		printf("entre \n");
		free(str);////////
		return (NULL);
	}
	x = 0;
	tmp = (char *)malloc(sizeof(char) * (((int)ft_strlen(str) - e) + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	while (str[e] != '\0')
	{
		tmp[x++] = str[e++];
	}
	free(str);
	tmp[x] = '\0';
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
