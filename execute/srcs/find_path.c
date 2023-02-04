/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:04:16 by wmari             #+#    #+#             */
/*   Updated: 2023/01/31 17:54:19 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	free_all(char **str)
{
	int	n;

	n = 0;
	if (str)
	{
		while (str[n])
			free(str[n++]);
		free(str[n]);
		free(str);
	}
}

static char	*my_getenv(t_mimi *shell)
{
	t_list	*temp;

	temp = shell->envlist;
	while (temp)
	{
		if (!check_same_till_equals(temp->str, "PATH="))
			return (temp->str);
		temp = temp->next;
	}
	return (NULL);
}

static char	*test_for_first(char **split, char *cmd)
{
	char	*temp;
	char	*temp2;

	temp = ft_strdup(split[0] + 5);
	temp2 = ft_strjoin(temp, "/");
	free(temp);
	temp = ft_strjoin(temp2, cmd);
	free(temp2);
	if (access(temp, F_OK & X_OK) == 0)
		return (temp);
	free(temp);
	return (NULL);
}

char	*find_path(char *cmd, t_mimi *shell)
{
	char	**splited_path;
	char	*temp;
	char	*temp2;
	int		n;

	if (my_getenv(shell) == NULL)
		return (cmd);
	splited_path = ft_split(my_getenv(shell), ':');
	if (splited_path == NULL)
		return (NULL);
	n = 1;
	temp = test_for_first(splited_path, cmd);
	if (temp)
		return (free_all(splited_path), temp);
	while (splited_path[n])
	{
		temp2 = ft_strjoin("/", cmd);
		temp = ft_strjoin(splited_path[n++], temp2);
		free(temp2);
		if (access(temp, F_OK & X_OK) == 0)
			return (free_all(splited_path), temp);
		free(temp);
	}
	temp = ft_strdup(cmd);
	return (free_all(splited_path), temp);
}
