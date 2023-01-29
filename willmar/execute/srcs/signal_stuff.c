/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:02:38 by wmari             #+#    #+#             */
/*   Updated: 2023/01/29 14:51:20 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*mettre ici les fonctions pour gerer les signaux*/

static void	sig_int_in_parent(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDERR_FILENO);
}

static void	sig_int_hd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	g_ret = 1;
}

void	catch_signal(int mode)
{
	if (mode == MAIN)
	{
		signal(SIGINT, sig_int_in_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HD)
	{
		signal(SIGINT, sig_int_hd);
		signal(SIGQUIT, SIG_IGN);
	}
}
