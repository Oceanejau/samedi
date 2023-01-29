/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:00:00 by wmari             #+#    #+#             */
/*   Updated: 2023/01/16 14:47:15 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	make_envlist(t_mimi *shell)
{
	int	i;

	i = 0;
	shell->ret = 0;
	shell->envlist = NULL;
	while (shell->env[i])
		ft_lstadd_back(&shell->envlist, ft_lstnew(shell->env[i++]));
}

int	check_same_till_equals(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == s2[i] && s1[i] == '=')
		return (0);
	return (1);
}

char	**envlist_to_env(t_list *envlist)
{
	int		i;
	t_list	*temp;
	char	**env;

	i = 0;
	temp = envlist;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(*env) * (i + 1));
	i = 0;
	temp = envlist;
	while (temp)
	{
		env[i] = ft_strdup(temp->str);
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	free_envchar(t_mimi *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		free(shell->env[i++]);
	free(shell->env);
}
