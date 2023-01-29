/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:49:33 by wmari             #+#    #+#             */
/*   Updated: 2022/12/29 15:58:57 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	free_shell_list(t_list	*list)
{
	if (list->next)
		free_shell_list(list->next);
	free(list->str);
	free(list);
}

void	free_list(t_mimi *shell)
{
	if (shell->list)
		free_shell_list(shell->list);
	shell->list = NULL;
}
