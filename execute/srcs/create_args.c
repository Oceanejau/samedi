/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:11:15 by wmari             #+#    #+#             */
/*   Updated: 2023/01/31 16:07:22 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (0);
}

static int	is_there_a_file(t_mimi *shell, int index, int n)
{
	t_list	*temp;
	int		comp;

	comp = 0;
	temp = shell->list;
	while (temp && comp != index)
	{
		if (temp->type == PIPE)
			comp++;
		temp = temp->next;
	}
	comp = 0;
	while (temp && comp != n)
	{
		temp = temp->next;
		comp++;
	}
	if (temp->next && temp->next->type == TXT && temp->next->str)
		return (0);
	return (1);
}

static int	count_args(char ***block, int index, t_mimi *shell)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (block[index][i])
	{
		if (is_redir(block, index, i, shell))
		{
			if (!is_there_a_file(shell, index, i))
				skip_redir(block, index, &i, shell);
			else
				return (ft_putstr_fd("Redirection unclear\n",
						STDERR_FILENO), -1);
		}
		else
		{
			i++;
			n++;
		}
	}
	return (n);
}

static char	**free_all(char **args, int n)
{
	if (args)
	{
		while (args[n])
			free(args[n++]);
	}
	free(args);
	return (NULL);
}

char	**create_args(char ***block, int index, t_mimi *shell, int i)
{
	int		n;
	int		j;
	char	**args;

	n = count_args(block, index, shell);
	if (n == -1)
		return (NULL);
	args = ft_calloc(sizeof(char *), n + 1);
	j = 0;
	if (!args)
		return (NULL);
	while (i < n)
	{
		if (is_redir(block, index, i, shell))
			skip_redir(block, index, &i, shell);
		else
		{
			args[j] = ft_strdup(block[index][i]);
			if (!args[j])
				return (free_all(args, n));
			j++;
		}
		i++;
	}
	return (args);
}
