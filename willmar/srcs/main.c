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

//#include "minishell.h"
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

	(void)av;
	shell = (t_mimi){0};
	g_ret = 0;
	if (ac != 1)
		return (ret_nb(126, "minishell cannot be executed with arguments\n",
				&shell));
	set_stuff(&shell, envp);
	while (shell.fin == 0)
	{
		catch_signal(MAIN);
		free_envchar(&shell);
		shell.env = envlist_to_env(shell.envlist);
		shell.line = readline("🐚mimishell🐚 ");
		rl_on_new_line();
		if (!shell.line)
			return (free_env(&shell), free_list(&shell), free_fd((&shell)->save_fd), free_tab(shell.env), 0);
		add_history(shell.line);
		mani(&shell);
	//	printf("MAin again\n");
		show_list(&shell);
//		new = next_hd(&shell, 2);
//		printf("STR  ======= %s\n",new->str);
		///show_list(&shell);
		better_exec(list_to_block((&shell)->list), &shell);
		// printf("end of exec\n");
		reset_stuff(&shell);
	}
	return (0);
}