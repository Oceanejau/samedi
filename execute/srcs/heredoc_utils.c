/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:04:50 by wmari             #+#    #+#             */
/*   Updated: 2023/02/07 19:33:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*get_name(int index)
{
	char	*nb;
	char	*ret;

	nb = ft_itoa(index);
	if (!nb)
	{
		ft_putstr_fd("gen_name: malloc fail\n", STDERR_FILENO);
		return (NULL);
	}
	ret = ft_strjoin("hold/temp", nb);
	free(nb);
	return (ret);
}

int	create_file(char *name, t_mimi *shell)
{
	int	fd;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, 0777);
	if (fd == -1)
		ft_putstr_fd("file creation fail", STDERR_FILENO);
	else
		shell->hd.nb_to_close++;
	return (fd);
}

char	*get_delim(t_mimi *shell)
{
	t_list	*temp;
	char	*delim;

	delim = NULL;
	temp = shell->list;
	while (temp)
	{
		if (!ft_strncmp("<<", temp->str, ft_strlen("<<"))
			&& temp->type == REDIR)
			break ;
		temp = temp->next;
	}
	if (temp && temp->next)
		delim = ft_strdup(temp->next->str);
	return (delim);
}

int	write_in_hd(t_mimi *shell, int index, char *delim)
{
	char	*str;

	if (delim == NULL)
		return (1);
	while (1)
	{
		str = readline(">");
		if (g_ret == 130)
			break ;
		if (!str)
			return (ft_putstr_fd("warning :here-document delimited by EOF\n",
					STDERR_FILENO), free(delim), free(str), 1);
		if (!ft_strncmp(delim, str, ft_strlen(delim)))
			return (free(delim), free(str), 0);
		while (next_kote(str, '$', 0) != -1)
			str = dollary(str, shell, 0);
		write(shell->hd.tab_fd[index], str, ft_strlen(str));
		write(shell->hd.tab_fd[index], "\n", 1);
		free(str);
	}
	if (g_ret == 130)
		free(delim);
	return (1);
}

void	free_hd(t_mimi *shell)
{
	int	i;

	i = 0;
	if (shell->hd.tab_fd)
	{
		while (i < shell->hd.nb_to_close)
		{
			if (shell->hd.tab_fd[i])
				close(shell->hd.tab_fd[i]);
			i++;
		}
		free(shell->hd.tab_fd);
	}
}
