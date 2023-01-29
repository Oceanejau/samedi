/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:06:30 by wmari             #+#    #+#             */
/*   Updated: 2022/12/20 20:40:35 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

char	*find_cmd(char **block)
{
	int		n;
	char	*found;

	n = 0;
	found = NULL;
	while (block[n])
	{
		if (!is_redir(block[n]))
		{
			if (!found)
				return (ft_strdup(block[n]));
		}
		else
			n++;
		n++;
	}
	return (found);
}
