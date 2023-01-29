/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:04:16 by wmari             #+#    #+#             */
/*   Updated: 2023/01/19 16:47:39 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	free_all(char **str)
{
	int	n;

	n = 0;
	while (str[n])
		free(str[n++]);
	free(str[n]);
	free(str);
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
	n = 0;
	temp = splited_path[n];
	splited_path[n] = ft_substr(splited_path[n], 5,
			splited_path[n] - ft_strchr(splited_path[n], ':'));
	free(temp);
	while (splited_path[n])
	{
		temp2 = ft_strjoin("/", cmd);
		temp = ft_strjoin(splited_path[n], temp2);
		free(temp2);
		if (access(temp, F_OK & X_OK) == 0)
			return (free_all(splited_path), temp);
		free(temp);
		n++;
	}
	free_all(splited_path);
	return (cmd);
}
