/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:46:04 by wmari             #+#    #+#             */
/*   Updated: 2023/02/09 16:23:46 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	maj_pwd(t_mimi *shell)
{
	char	*str;
	t_list	*temp;

	str = ft_calloc(sizeof(char), 1024);
	if (!str)
		return ;
	getcwd(str, 1023);
	temp = shell->envlist;
	while (temp)
	{
		if (!check_same_till_equals("PWD=", temp->str))
		{
			free(temp->str);
			temp->str = ft_strjoin("PWD=", str);
			break ;
		}
		temp = temp->next;
	}
	free(str);
}

static void	error_msg_cd(char **args, char ***block, t_mimi *shell, char *save)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_alloc_cd(block, shell, save, args);
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

static void	do_home(t_mimi *shell, char *save)
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
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
}

int	ft_cd(char ***block, int index, t_mimi *shell, int *fbp)
{
	char	*save;
	char	**args;

	if (nb_args(block[index]) > 2)
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO),
			free_block(block), 1);
	args = create_args(block, index, shell);
	if (!args)
		return (return_error(block, fbp, shell));
	save = ft_calloc(sizeof(char), 1024);
	if (!save)
		return (free_tab(args), return_error(block, fbp, shell));
	getcwd(save, 1023);
	if (args[1])
	{
		if (!chdir(args[1]))
			add_oldpwd(shell, save);
	}
	else
		do_home(shell, save);
	if (count_pipe(shell))
		close (*fbp);
	if (errno)
		return (error_msg_cd(args, block, shell, save), 1);
	return (maj_pwd(shell), free_alloc_cd(block, shell, save, args));
}
