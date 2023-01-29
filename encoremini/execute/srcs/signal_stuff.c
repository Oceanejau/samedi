/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:02:38 by wmari             #+#    #+#             */
/*   Updated: 2023/01/23 14:59:53 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*mettre ici les fonctions pour gerer les signaux*/

void	sig_int_in_parent(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_quit_in_child(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	exit(131);
}