/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:28:17 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 16:48:06 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	g_ret;

static void	set_stuff(t_mimi *shell, char **envp)
{
	set_struct(shell, envp);
	make_envlist(shell);
	set_fd(shell->save_fd);
}

static void	reset_stuff(t_mimi *shell)
{
	reset_fd(shell->save_fd);
	free_list(shell);
	if (shell->nb_hd > 0)
		free_hd(shell);
}

int	ret_nb(int ret, char *msg, t_mimi *shell)
{
	shell->ret = ret;
	write(2, "Error : minishell ", 19);
	write(2, msg, ft_strlen(msg));
	return (ret);
}

void	starter(t_mimi *shell)
{
	catch_signal(MAIN);
	free_envchar(shell);
	shell->env = envlist_to_env(shell->envlist);
}

int	main(int ac, char **av, char **envp)
{
	t_mimi	shell;

	(void)av;
	shell = (t_mimi){0};
	if (ac != 1)
		return (ret_nb(126, "cannot be executed with arguments\n", &shell));
	set_stuff(&shell, envp);
	while (shell.fin == 0)
	{
		starter(&shell);
		shell.line = readline("🐚mimishell🐚 ");
		rl_on_new_line();
		if (!shell.line)
			return (free_env(&shell), free_list(&shell),
				free_fd((&shell)->save_fd), free_tab(shell.env), 0);
		add_history(shell.line);
		mani(&shell, 0);
		show_list(&shell);
		g_ret = 0;
		heredoc_init(&shell);
		if (g_ret != 130)
			better_exec(list_to_block((&shell)->list), &shell);
		reset_stuff(&shell);
	}
	return (0);
}
