/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:06:30 by wmari             #+#    #+#             */
/*   Updated: 2023/01/26 19:59:53 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

char	*find_cmd(char ***block, int index, t_mimi *shell)
{
	int		n;
	char	*found;

	n = 0;
	found = NULL;
	while (block[index][n])
	{
		if (!is_redir(block, index, n, shell))
		{
			if (!found)
				return (ft_strdup(block[index][n]));
		}
		else
			n++;
		n++;
	}
	return (found);
}
