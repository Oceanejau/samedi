/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:28:17 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 06:48:34 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "execute.h"

int	g_ret;

void	show_list(t_mimi *shell)
{
	t_list	*new;

	new = shell->list;
	printf("showlist main\n");
	printf("str prev %s\n", new->str);
	while (new != NULL)
	{
		printf("str = -%s- type = %d\n", new->str, new->type);
		new = new->next;
	}
	printf("fin list\n");
	return ;
}

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
	return ;
}

static void	set_stuff(t_mimi *shell, char **envp, int **save_fd)
{
	set_struct(shell, envp);
	make_envlist(shell);
	set_fd(save_fd);
}

static void	reset_stuff(t_mimi *shell, int **save_fd)
{
	reset_fd(save_fd);
	free_list(shell);
}

int	ret_nb(int ret, char *msg, t_mimi *shell)
{
	shell->ret = ret;
	write(2, "Error : ", 9);
	write(2, msg, ft_strlen(msg));
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	t_mimi	shell;
	int		*save_fd;

	(void)av;
	shell = (t_mimi){0};
	g_ret = 0;
	if (ac != 1)
		return (ret_nb(126, "minishell cannot be executed with arguments\n",
				&shell));
	set_stuff(&shell, envp, &save_fd);
	while (shell.fin == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_int_in_parent);
		free_envchar(&shell);
		shell.env = envlist_to_env(shell.envlist);
		shell.line = readline("🐚mimishell🐚 ");
		rl_on_new_line();
		if (!shell.line)
			return (int_err("readline fucked up", 2));
		add_history(shell.line);
		mani(&shell);
	//	printf("MAin again\n");
		show_list(&shell);
//		new = next_hd(&shell, 2);
//		printf("STR  ======= %s\n",new->str);
		///show_list(&shell);
		better_exec(list_to_block((&shell)->list), &shell);
		// printf("end of exec\n");
		reset_stuff(&shell, &save_fd);
	}
	return (0);
}
