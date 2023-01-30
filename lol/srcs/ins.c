/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:57:00 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:57:11 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "minishell.h"

char	*cut_in(char *str, int x)
{
	int		y;
	char	*tmp;

	y = 0;
	//printf("cut_in %s, %d\n", str, x);
	if (str[0] == '\0')
	{
		// free(str);
		return (NULL);
	}
	if ((int)ft_strlenn(str) <= x)
	{
		printf("je free ici\n");
		// free(str);
	// 	str = NULL;
		return (NULL);
	}
	while (str[x + y] != '\0')
		y++;
	if (y == 0)
	{
		// free(str);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (y + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	y = 0;
	while (str[x + y] != '\0')
	{
		tmp[y] = str[x + y];
		y++;
	}
	tmp[y] = '\0';
	// free(str);
	printf("cut in tmp = %s\n", tmp);
	return (tmp);
}

char	*cut_in_it(t_mimi *shell, char *str, int x, int size)
{
	int		y;
	char	*tmp;

	
	y = 0;
//	printf("cut_in %s, %d, %s\n", str, x, shell->line);
	if (str == NULL)
	{
	//	free(str);
		return (NULL);
	}
	if ((int)ft_strlenn(str) <= x)
	{
		printf("je free ici\n");
		free(str);
		if (shell->s == size)
			shell->line = NULL;
	// 	str = NULL;
		return (NULL);
	}
	while (str[x + y] != '\0')
		y++;
	if (y == 0)
	{
		free(str);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (y + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	y = 0;
	while (str[x + y] != '\0')
	{
		tmp[y] = str[x + y];
		y++;
	}
	tmp[y] = '\0';
	free(str);
	printf("cut in tmp = %s\n", tmp);
	return (tmp);
}

char	*get_in(char *str, int x)
{
	char	*tmp;
	int		y;

	y = 0;
//	printf("str = %s, x = %d\n", str, x);
	if (x == 0)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (x + 1));
	if (tmp == NULL)
		return (NULL);
	while (x > y)
	{
		tmp[y] = str[y];
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}
