/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:24:30 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:31:35 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	poplist(t_mimi *shell, t_list *pop)
{
	t_list	*temp;

	temp = shell->envlist;
	if (pop == shell->envlist)
	{
		if (shell->envlist->next)
			shell->envlist = shell->envlist->next;
		else
			shell->envlist = NULL;
		free(pop->str);
		free(pop);
	}
	else
	{	
		while (temp && temp->next != pop)
			temp = temp->next;
		temp->next = pop->next;
		free(pop->str);
		free(pop);
	}
}

static int	error_unset(char ***block, t_mimi *shell, int *fbp)
{
	ft_putstr_fd("Error, can't create arguments\n", STDERR_FILENO);
	if (count_pipe(shell))
	{
		free_block(block);
		close(*fbp);
		free_list(shell);
		free_tab(shell->env);
		free_env(shell);
		free_sfd(shell->save_fd);
		exit(1);
	}
	return (1);
}

static int	return_normal_unset(
	char ***block,
	t_mimi *shell,
	int *fbp,
	char **args)
{
	free_tab(args);
	if (count_pipe(shell))
	{
		free_block(block);
		close(*fbp);
		free_list(shell);
		free_tab(shell->env);
		free_env(shell);
		free_sfd(shell->save_fd);
		exit(0);
	}
	return (0);
}

int	ft_unset(char ***block, int index, t_mimi *shell, int *fbp)
{
	int		i;
	char	**args;
	t_list	*temp;

	args = create_args(block, index, shell);
	if (!args)
		return (error_unset(block, shell, fbp));
	i = 0;
	while (args[i])
	{
		temp = shell->envlist;
		while (temp)
		{
			if (!ft_strncmp(args[i], temp->str,
					ft_strlen(args[i]))
				&& temp->str[ft_strlen(args[i])] == '=')
			{
				poplist(shell, temp);
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
	return (return_normal_unset(block, shell, fbp, args));
}
