/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:27:24 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:53:24 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_stuff(char ***block, int index, int *fbp, t_mimi *shell)
{
	char	*cmd;

	cmd = find_cmd(shell, index);
	if (cmd)
	{
		if (builtin_finder(cmd) != -1)
			return (free(cmd), exec_builtin(block, index, fbp, shell));
		else if (block[index][0][0] == '\0')
			return (free(cmd), exec_empty(block, index, fbp, shell));
		else
			return (free(cmd), exec_bin(block, index, fbp, shell));
	}
	else
		create_file_redir(shell, index);
	return (0);
}
