/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:08:13 by wmari             #+#    #+#             */
/*   Updated: 2023/01/31 17:33:16 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	free_block(char ***block)
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
	}
}

static void	add_oldpwd(t_mimi *shell, char *str)
{
	t_list	*temp;
	char	*save;

	temp = shell->envlist;
	while (temp)
	{
		if (!check_same_till_equals("OLDPWD=", temp->str))
		{
			free(temp->str);
			temp->str = ft_strjoin("OLDPWD=", str);
			break ;
		}
		temp = temp->next;
	}
	if (!temp)
	{
		save = ft_strjoin("OLDPWD=", str);
		ft_lstadd_back(&(shell->envlist),
			ft_lstnew(save));
		free(save);
	}
}

static int	do_home(t_mimi *shell, char *save)
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
	{
		if (!chdir(str))
			add_oldpwd(shell, save);
		free(str);
	}
	else
		printf("cd: HOME not set\n");
	return (0);
}

int	ft_cd( char ***block, int index, t_mimi *shell)
{
	int		n;
	char	*save;

	n = 0;
	while (block[index][n])
		n++;
	if (n > 2)
		return (printf("cd: too many arguments\n"), 1);
	save = ft_calloc(sizeof(char), 1024);
	getcwd(save, 1023);
	if (block[index][1])
	{
		if (!chdir(block[index][1]))
			add_oldpwd(shell, save);
	}
	else
		do_home(shell, save);
	if (errno)
		return (free(save), printf("cd: %s: %s\n", block[index][1],
			strerror(errno)), 1);
	free_block(block);
	free_list(shell);
	return (free(save), 0);
}

int	ft_solocd(char ***block, int index, t_mimi *shell)
{
	int		n;
	char	*save;

	n = 0;
	while (block[index][n])
		n++;
	if (n > 2)
		return (printf("cd: too many arguments\n"), 1);
	save = ft_calloc(sizeof(char), 1024);
	getcwd(save, 1023);
	if (block[index][1])
	{
		if (!chdir(block[index][1]))
			add_oldpwd(shell, save);
	}
	else
		do_home(shell, save);
	if (errno)
		return (free(save), printf("cd: %s: %s\n", block[index][1],
			strerror(errno)), 1);
	return (free(save), 0);
}
