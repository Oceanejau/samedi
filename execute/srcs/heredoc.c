/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:01:31 by wmari             #+#    #+#             */
/*   Updated: 2023/01/30 22:53:05 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	heredoc(t_mimi *shell, int index)
{
	int		holder_fd;
	char	*filename;

	holder_fd = dup(STDIN_FILENO);
	filename = get_name(index);
	shell->hd.tab_fd[index] = create_file(filename, shell);
	free(filename);
	if (shell->hd.tab_fd[index] == -1)
		return (1);
	write_in_hd(shell, index, get_delim(shell));
	dup2(holder_fd, STDIN_FILENO);
	close(holder_fd);
	return (0);
}

int	modif_list(t_mimi *shell, int index)
{
	t_list	*temp;
	char	*copy;

	temp = shell->list;
	while (temp)
	{
		if (!ft_strncmp("<<", temp->str, ft_strlen("<<"))
			&& temp->type == REDIR)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (0);
	copy = ft_itoa(index);
	free(temp->str);
	temp->str = ft_strdup("<");
	free(temp->next->str);
	temp->next->str = ft_strjoin("hold/temp", copy);
	free(copy);
	return (0);
}

int	heredoc_init(t_mimi *shell)
{
	int	status;

	status = 0;
	catch_signal(HD);
	if (!shell->nb_hd)
		return (0);
	shell->hd.tab_fd = (int *)malloc(sizeof(int) * shell->nb_hd);
	if (!shell->hd.tab_fd)
		return (1);
	shell->hd.index = 0;
	shell->hd.nb_to_close = 0;
	while (shell->hd.index < shell->nb_hd)
	{
		status = heredoc(shell, shell->hd.index);
		if (status)
			return (0);
		modif_list(shell, shell->hd.index);
		shell->hd.index++;
	}
	return (0);
}
