/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 08:23:51 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 08:23:57 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_list	*join_list(t_list *s1, t_list *s2)
{
	t_list	*new;

	while (s1 != NULL)
	{
		ft_listadd_back(&new, ft_listnew(s1->str, s1->type));
		s1 = s1->next;
	}
	while (s2 != NULL)
	{
		ft_listadd_back(&new, ft_listnew(s2->str, s2->type));
		s2 = s2->next;
	}
	return (new);
}

void	dol_suite(t_mimi *shell, int y, int x)
{
	t_mimi	reshell;

	reshell = (t_mimi){0};
	set_struct_bis(&reshell);
	shell->tmp = joi(shell->tmp, cpy_from_two_pos(shell->t, 0, x - 1));
	shell->f_env = find_env(cftp(shell, x, x + y), shell);
	if (shell->kote != 39 && shell->f_env != NULL)
	{
		reshell.line = join(shell->tmp, shell->f_env);
		reshell.exp = 1;
		mani(&reshell, 0);
		printf("reshell-> %s, %s, %d\n", shell->tmp, shell->t, x);
		show_list(&reshell);
		if (shell->tmp != NULL)
		{
			ft_listadd_back(&shell->list, ft_listnew(shell->tmp, shell->type));
			free(shell->tmp);
			printf("re\n");
			shell->tmp = NULL;
		//	printf("passe le if\n");
			shell->list = join_list(shell->list, reshell.list);
		}
		else
		{
			shell->list = reshell.list;
		//	free(shell->f_env);
			shell->f_env = NULL;
		}
		//	join des deux lists;
	}
	if (shell->f_env != NULL)
		shell->tmp = joi(shell->tmp, shell->f_env);
	printf("tmp = %s\n", shell->tmp);
	//	shell->f_env = find_env39(cftp(shell, x, x + y), shell);
	//else
	//	shell->f_env = find_env(cftp(shell, x, x + y), shell);
	
}

int	dol(t_mimi *shell, int y, int x)
{
	if (ft_is_nb(shell->t[x]) == 1 && y == 0)
	{
		shell->tmp = joi(shell->tmp, cpy_from_two_pos(shell->t, 0, x - 1));
		y++;
	}
	else
	{
		while ((ft_is_nb(shell->t[x + y]) == 1 || ft_is_alpha(shell->t[x + y])
				== 1 || shell->t[x + y] == '_') && shell->t[x + y] != '\0')
			y++;
		if (shell->t[x] == '?')
		{
			shell->tmp = joi(shell->tmp, ft_itoaa(g_ret));
			y++;
		}
		else if (y == 0)
		{
			shell->tmp = join(shell->tmp, malicious("$"));
			y = 0;
		}
		else
			dol_suite(shell, y, x);
	}
	return (y);
}

int	dollll_fin(t_mimi *shell, int x, int y)
{
	char	*copy;

	copy = ft_strdup(shell->t);
	free(shell->t);
	shell->t = cut_i(copy, x + y);
	free(copy);
	return (-1);
}

char	*dollar(char*str, t_mimi *shell, int x)//speciale kote
{
	int		y;

	shell->tmp = NULL;
	shell->t = str;
	shell->kote = 39;
	while (shell->t && shell->t[x] != '\0')
	{
		y = 0;
		if (shell->t[x] == '$')
		{
			x++;
			y = dol(shell, y, x);
			x = dollll_fin(shell, x, y);
		}
		else
		{
			shell->tmp = joi(shell->tmp, cpy_from_two_pos(shell->t, 0, x + 1));
			x = dollll_fin(shell, x, 1);
		}
		x++;
	}
	shell->kote = 0;
	return (shell->tmp);
}

char	*dollary(char*str, t_mimi *shell, int x)
{
	int		y;

	if (shell->exp != 1)
	{
		shell->tmp = NULL;
		shell->t = str;
		while (shell->t && shell->t[x] != '\0')
		{
			y = 0;
			if (shell->t[x] == '$')
			{
				x++;
				y = dol(shell, y, x);
				x = dollll_fin(shell, x, y);
			}
			else
			{
				shell->tmp = joi(shell->tmp, cpy_from_two_pos(shell->t, 0, x + 1));
				x = dollll_fin(shell, x, 1);
			}
			x++;
		}
	}
	else
		return (str);
	return (shell->tmp);
}
