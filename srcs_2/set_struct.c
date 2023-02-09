/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 07:26:19 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 15:10:43 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static char	**my_env(void)
{
	char	**env;
	char	*temp;
	char	*temp2;

	env = ft_calloc(3, sizeof(char *));
	env[0] = ft_strdup("SHLVL=1");
	temp = malloc(1024);
	getcwd(temp, 1023);
	temp2 = ft_strjoin("PWD=", temp);
	env[1] = ft_strdup(temp2);
	free(temp);
	free(temp2);
	env[2] = NULL;
	return (env);
}

void	set_struct(t_mimi *shell, char **envp)
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
	if (!shell->env[0])
	{
		free_env(shell->env);
		shell->env = my_env();
	}
	g_ret = 0;
	return ;
}

void	set_struct_bis(t_mimi *shell)
{
	shell->instr[0] = ' ';
	shell->instr[1] = '\t';
	shell->instr[2] = '\'';
	shell->instr[3] = '"';
	shell->instr[4] = '|';
	shell->instr[5] = '>';
	shell->instr[6] = '<';
	shell->instr[7] = '\0';
	g_ret = 0;
	return ;
}
