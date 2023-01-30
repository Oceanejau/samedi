/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:03:05 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 05:03:08 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*do_end(t_mimi *shell)
{
	char	*str;
	char	*tmp;
	int		x;
//	int		y;

	x = 0;
	tmp = NULL;
	str = ft_strdup(shell->line);
	printf("do_end===================\n");
	while (str && str[x] != '\0')
	{
		if (str[x] == '$')
		{
	//		printf("$$$$$\n");
			tmp = join(tmp, dollary(str, shell, x));
		//	free(str);
		//	str = NULL;
			//printf("tmp = -%s- size = %d, %d\n", tmp, shell->size, x);
			//y = ft_strlenn(dollary(str, shell, x));
			if (shell->size/*y*/ == 0)
			{
				shell->line = NULL;
				return (tmp);
			}
		//	printf("%s\n", str);
			//exit (0);
			if (shell->line == NULL || !str)
			{
				printf("STRRTRTRTRT\n");
				//free(str);
				return (tmp);
			}
			shell->line = NULL;
			return (tmp);
		//	printf("str = -%s- \n", shell->line);
		//	if (shell->size == (int)ft_strlenn(str))
		//		shell->line = NULL;
		//	if (str)
		//		str = cut_from_pos(str, x + /*y*/shell->size);
		}
		else
		{
			tmp = join(tmp, cpy_from_two_pos(str, 0, x + 1));
			str = cut_from_pos(str, x + 1);
		}
		x = 0;
	}
	printf("finde de while\n");
	shell->line = NULL;
	if (tmp != NULL)
		return (tmp);
	free(tmp);
	return (str);
}
