/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:01:09 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:31:17 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	add_stuff_export(char *str, t_list *temp)
{
	char	*copy;
	char	*copy2;
	char	*copy3;

	copy = ft_strdup(temp->str);
	free(temp->str);
	copy3 = ft_strjoin(":", ft_strchr(str, '=') + 1);
	copy2 = ft_strjoin(copy, copy3);
	temp->str = ft_strdup(copy2);
	free(copy3);
	free(copy2);
	free(copy);
}

static int	check_valid_arg(char *str)
{
	int	i;
	int	name;
	int	equals;
	int	def;

	i = 0;
	name = 0;
	equals = 0;
	def = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != '=')
			name = 1;
		else if (str[i] == '=')
			equals++;
		else if (str[i] != '=' && name == 1)
			def = 1;
		i++;
	}
	if (name == 1 && equals == 1 && def == 1)
		return (1);
	return (0);
}

static void	do_stuff_valid(char *str, t_mimi *shell)
{
	t_list	*temp;

	if (check_valid_arg(str))
	{
		temp = shell->envlist;
		while (temp)
		{
			if (!check_same_till_equals(str, temp->str))
			{
				free(temp->str);
				temp->str = ft_strdup(str);
				break ;
			}
			if (!check_if_add(str, temp->str))
			{
				add_stuff_export(str, temp);
				break ;
			}
			temp = temp->next;
		}
		if (!temp)
			ft_lstadd_back(&(shell->envlist), ft_lstnew(str));
	}
}

static int	return_exit(char ***block, char **args, t_mimi *shell, int *fbp)
{
	int	cmd;

	cmd = count_pipe(shell);
	free_tab(args);
	if (cmd)
	{
		free_block(block);
		free_tab(shell->env);
		free_env(shell);
		free_list(shell);
		free_sfd(shell->save_fd);
		close(*fbp);
		exit(0);
	}
	return (0);
}

int	ft_export(char ***block, int index, t_mimi *shell, int *fbp)
{
	int		i;
	char	**args;

	args = create_args(block, index, shell);
	if (!args)
		return_error(block, fbp, shell);
	i = 1;
	while (args[i])
	{
		do_stuff_valid(args[i], shell);
		i++;
	}
	return (return_exit(block, args, shell, fbp));
}
