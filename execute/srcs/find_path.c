/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:37:28 by wmari             #+#    #+#             */
/*   Updated: 2023/02/07 19:33:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*get_first_path(char *split, char *cmd)
{
	char	*temp;
	char	*temp2;

	temp = ft_strdup(split + 5);
	if (!temp)
		return (NULL);
	temp2 = ft_strjoin(temp, "/");
	free(temp);
	temp = ft_strjoin(temp2, cmd);
	free(temp2);
	if (access(temp, F_OK & X_OK) == 0)
		return (temp);
	free(temp);
	return (NULL);
}

static char	*get_path(char *split, char *cmd)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (NULL);
	temp2 = ft_strjoin(split, temp);
	if (!temp2)
		return (free(temp), NULL);
	return (free(temp), temp2);
}

static int	is_there_path(t_mimi *shell)
{
	t_list	*temp;

	temp = shell->envlist;
	while (temp)
	{
		if (!ft_strncmp(temp->str, "PATH=", 5))
			return (0);
		temp = temp->next;
	}
	return (1);
}

static char	*getpath(t_mimi *shell)
{
	t_list	*temp;

	temp = shell->envlist;
	while (temp)
	{
		if (!ft_strncmp(temp->str, "PATH=", 5))
			return (temp->str);
		temp = temp->next;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_mimi *shell, int n)
{
	char	**splited_path;
	char	*temp;

	if (is_there_path(shell))
		return (ft_strdup(cmd));
	splited_path = ft_split(getpath(shell), ':');
	if (!splited_path)
		return (NULL);
	temp = get_first_path(splited_path[0], cmd);
	if (temp)
		return (free_tab(splited_path), temp);
	while (splited_path[n])
	{
		temp = get_path(splited_path[n++], cmd);
		if (!temp)
			return (free_tab(splited_path), NULL);
		if (access(temp, F_OK & X_OK) == 0)
			return (free_tab(splited_path), temp);
		free(temp);
	}
	temp = ft_strdup(cmd);
	return (free_tab(splited_path), temp);
}
