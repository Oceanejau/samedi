/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:48:27 by wmari             #+#    #+#             */
/*   Updated: 2023/01/31 12:18:55 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	free_block(char ***block, t_mimi *shell)
{
	int	i;
	int	j;

	i = 0;
	if (block)
	{
		while (block[i])
		{
			j = 0;
			while (block[i][j])
			{
				free(block[i][j]);
				j++;
			}
			free(block[i][j]);
			free(block[i]);
			i++;
		}
		free(block[i]);
		free(block);
		free_list(shell);
	}
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

int	ft_export(char ***block, int index, t_mimi *shell)
{
	int		i;

	i = 0;
	while (block[index][++i])
	{
		do_stuff_valid(block[index][i], shell);
		i++;
	}
	free_block(block, shell);
	return (0);
}

int	ft_soloexport(char ***block, int index, t_mimi *shell)
{
	int		i;

	i = 1;
	while (block[index][i])
	{
		do_stuff_valid(block[index][i], shell);
		i++;
	}
	return (0);
}
