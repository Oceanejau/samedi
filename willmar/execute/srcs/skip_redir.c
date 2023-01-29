/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:44:46 by wmari             #+#    #+#             */
/*   Updated: 2023/01/25 15:50:27 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	skip_redir(char ***block, int index, int *n, t_mimi *shell)
{
	if (is_redir(block, index, *n, shell))
		*n = *n + 2;
}
