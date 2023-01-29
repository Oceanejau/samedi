/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:08:13 by wmari             #+#    #+#             */
/*   Updated: 2023/01/23 16:06:55 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

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

static int do_home(t_mimi *shell)
{
	t_list	*temp;
	char	*str;

	temp = shell->envlist;
	str = NULL;
	while (temp)
	{
		if (!ft_strncmp(temp->str, "HOME=", 5))
			str = ft_substr(temp->str, 5, ft_strlen(temp->str + 5));
		temp = temp->next;
	}
	if (str)
		chdir(str);
	else
		printf("cd: HOME not set\n");
	return (0);
}

int	ft_cd( char ***block, int index, t_mimi *shell)
{
	int	n;

	n = 0;
	while (block[index][n])
		n++;
	if (n > 2)
	{
		printf("cd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (block[index][1])
		chdir(block[index][1]);
	else
		do_home(shell);
	if (errno)
		perror("cd");
	free_block(block);
	free_list(shell);
	exit(EXIT_SUCCESS);
}

int	ft_solocd(char ***block, int index, t_mimi *shell)
{
	int	n;

	n = 0;
	while (block[index][n])
		n++;
	if (n > 2)
	{
		printf("cd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (block[index][1])
		chdir(block[index][1]);
	else
		do_home(shell);
	if (errno)
		return (printf("cd: %s: %s\n", block[index][1],
			strerror(errno)), 1);
	return (0);
}
