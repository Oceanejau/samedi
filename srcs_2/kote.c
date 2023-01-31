/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kote.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:52:32 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 07:48:38 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*johnny(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*tmp;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s2);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	x = -1;
	while (s1[++x] != '\0')
		tmp[x] = s1[x];
	y = -1;
	while (s2[++y] != '\0')
		tmp[x + y] = s2[y];
	tmp[x + y] = '\0';
	free(s1);
	free(s2);
	return (tmp);
}

int	where_is_charly(char *str, int x, char c)
{
	while (str[x] != '\0')
	{
		if (str[x] == c)
			return (x);
		x++;
	}
	return (-1);
}

void	mani_free(t_mimi *shell, char *str)
{
	free_list(shell);
	free(shell->line);
	free(str);
}

int	mani(t_mimi *shell)
{
	char	*str;
	int		x;

	str = NULL;
	shell->quote = 0;
	shell->nb_hd = 0;
	x = 0;
	while (shell->line != NULL && shell->line[x] != '\0')
	{
		if (str_c(shell->instr, shell->line[x]) != 10
			|| shell->line[x + 1] == '\0')
		{
			str = repartiteur(shell, x, str);
			x = -1;
			if (str == NULL && shell->ret == -1)
				mani_free(shell, str);
			else if (str != NULL && ft_strlen(str) != 0)
			{
				ft_listadd_back(&shell->list, ft_listnew(str, shell->type));
				free(str);
			}
			shell->fre = 0;
			shell->same = 0;
		}
		x++;
	}
	return (0);
}
