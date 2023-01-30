/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:56:45 by wmari             #+#    #+#             */
/*   Updated: 2023/01/27 15:26:51 by wmari            ###   ########.fr       */
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

int	ft_solopwd(char ***block, int index)
{
	char	*str;

	(void)index;
	(void)block;
	str = ft_calloc(sizeof(char), 1024);
	if (!str)
	{
		perror("malloc");
		return (1);
	}
	getcwd(str, 1023);
	printf("%s\n", str);
	free(str);
	return (0);
}

int	ft_pwd( char ***block, int index, t_mimi *shell)
{
	char	*str;

	(void)index;
	str = ft_calloc(sizeof(char), 1024);
	if (!str)
	{
		perror("malloc");
		return (1);
	}
	getcwd(str, 1023);
	printf("%s\n", str);
	free(str);
	free_block(block);
	free_list(shell);
	return (0);
}
