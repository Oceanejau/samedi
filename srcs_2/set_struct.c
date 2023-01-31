/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 07:26:19 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 07:26:24 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	set_struct(t_mimi	*shell, char **envp)
{
	shell->instr[0] = ' ';
	shell->instr[1] = '\t';
	shell->instr[2] = '\'';
	shell->instr[3] = '"';
	shell->instr[4] = '|';
	shell->instr[5] = '>';
	shell->instr[6] = '<';
	shell->instr[7] = '\0';
	shell->env = copy_char_et_et(envp);
	g_ret = 0;
	return ;
}
