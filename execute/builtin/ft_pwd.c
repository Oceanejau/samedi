/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:10:45 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:31:26 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	return_error_pwd(char ***block, t_mimi *shell, int *fbp)
{
	if (count_pipe(shell))
	{
		free_tab(shell->env);
		close(*fbp);
		free_list(shell);
		free_env(shell);
		free_block(block);
		free_sfd(shell->save_fd);
		exit(1);
	}
	g_ret = 1;
	return (0);
}

static int	return_normal_pwd(char ***block, t_mimi *shell, int *fbp)
{
	if (count_pipe(shell))
	{
		close(*fbp);
		free_tab(shell->env);
		free_list(shell);
		free_env(shell);
		free_block(block);
		free_sfd(shell->save_fd);
		exit(0);
	}
	g_ret = 0;
	return (0);
}

int	ft_pwd(char ***block, int index, t_mimi *shell, int *fbp)
{
	char	*str;

	(void)index;
	str = ft_calloc(sizeof(char), 1024);
	if (!str)
		return (perror("malloc:"), return_error_pwd(block, shell, fbp));
	getcwd(str, 1023);
	printf("%s\n", str);
	free(str);
	return (return_normal_pwd(block, shell, fbp));
}
