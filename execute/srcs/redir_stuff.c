/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:58:47 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 14:29:37 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	do_redirection(t_list *redir, t_list *file)
{
	if (!ft_strncmp(redir->str, ">>", ft_strlen(">>")))
		return (outfile_dou_modif(file->str));
	else if (!ft_strncmp(redir->str, ">", ft_strlen(">")))
		return (outfile_modif(file->str));
	else
		return (infile_modif(file->str));
}

int	redir_stuff(t_mimi *shell, int index)
{
	t_list	*temp;
	int		i;
	int		count_pipe;

	count_pipe = 0;
	temp = shell->list;
	while (temp && count_pipe < index)
	{
		if (temp->type == PIPE)
			count_pipe++;
		temp = temp->next;
	}
	i = 0;
	while (temp && !i && temp->type != PIPE)
	{
		if (temp->type == REDIR && temp->next->type == NAMEFILE)
			i = do_redirection(temp, temp->next);
		temp = temp->next;
	}
	return (i);
}

int	create_file_redir(t_mimi *shell, int index)
{
	if (redir_stuff(shell, index))
		return (1);
	reset_fd(shell->save_fd);
	return (0);
}
