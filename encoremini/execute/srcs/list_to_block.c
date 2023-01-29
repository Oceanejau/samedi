/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:41:30 by wmari             #+#    #+#             */
/*   Updated: 2022/12/29 14:43:32 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"

static int	count_pipe(t_list *list)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->str, "|", 1))
			i++;
		temp = temp->next;
	}
	return (i + 1);
}

static int	count_list(t_list *list)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = list;
	while (temp && ft_strncmp(temp->str, "|", 1))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

static void	fill_block(char ****block, int size, t_list *list)
{
	int		i;
	int		j;
	t_list	*temp;

	i = 0;
	temp = list;
	while (i < size)
	{
		(*block)[i] = (char **)ft_calloc(count_list(temp) + 1, sizeof(char *));
		j = 0;
		while (temp)
		{
			if (temp->str[0] == '|')
				break ;
			(*block)[i][j] = ft_strdup(temp->str);
			j++;
			temp = temp->next;
		}
		if (temp)
			temp = temp->next;
		(*block)[i][j] = NULL;
		i++;
	}
}

char	***list_to_block(t_list *list)
{
	int		i;
	char	***block;

	i = count_pipe(list);
	block = ft_calloc(i + 1, sizeof(char **));
	if (!block)
		return (NULL);
	fill_block(&block, i, list);
	block[i] = NULL;
	return (block);
}
