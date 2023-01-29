/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:36:12 by wmari             #+#    #+#             */
/*   Updated: 2023/01/11 17:55:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

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

static void	free_block(char ***block)
{
	int	i;
	int	j;

	i = 0;
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
}

int	ft_solounset(char ***block, int index, t_mimi *shell)
{
	int		i;
	t_list	*temp;

	i = 0;
	while (block[index][i])
	{
		temp = shell->envlist;
		while (temp)
		{
			if (!ft_strncmp(block[index][i], temp->str,
				ft_strlen(block[index][i]))
				&& temp->str[ft_strlen(block[index][i])] == '=')
			{
				poplist(shell, temp);
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
	return (0);
}

int	ft_unset(char ***block, int index, t_mimi *shell)
{
	int		i;
	t_list	*temp;

	i = 0;
	while (block[index][i])
	{
		temp = shell->envlist;
		while (temp)
		{
			if (!ft_strncmp(block[index][i], temp->str,
				ft_strlen(block[index][i]))
				&& temp->str[ft_strlen(block[index][i])] == '=')
			{
				poplist(shell, temp);
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
	free_block(block);
	free_list(shell);
	exit(EXIT_SUCCESS);
}
