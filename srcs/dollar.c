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

char	*bb_mid(t_mimi *shell, int x, int y)
{
	if (y == 0 && shell->t[x + y] == '?')
	{
		ptit_bidule(shell, x);
		x = 1;
	}
	else if ((shell->t && shell->t[x + y] != '\0' && shell->t[x + y] != '$'
			&& str_c(shell->instr, shell->t[x + y]) == 10)
		&& (ft_is_nb(shell->t[x + y]) == 1 || ft_is_alpha(shell->t[x + y])
			== 1 || shell->t[x + y] == '_'))
		return (char_err("something went wrong with this variable", 2));
	else if (y == 0)
		shell->tmp = joi(shell->tmp, malicious("$"));
	shell->tmp = join(shell->tmp, cpy_from_two_pos(shell->t, 0, x - 1));
	shell->f_env = find_env(cftp(shell, x, x + y), shell);
	if (shell->f_env != NULL)
		shell->tmp = joi(shell->tmp, shell->f_env);
	return (shell->tmp);
}

char	*doll(t_mimi *shell, int x)
{
	int	y;

	y = 0;
	if (ft_is_nb(shell->t[x]) == 1)
		dolly(shell, x);
	else if (ft_is_nb(shell->t[x]) != 1)
	{
		while ((ft_is_nb(shell->t[x + y]) == 1 || ft_is_alpha(shell->t[x + y])
				== 1 || shell->t[x + y] == '_') && shell->t[x + y] != '\0')
			y++;
		shell->tmp = bb_mid(shell, x, y);
		if (shell->vent != 0)
			y = shell->vent;
		else if (shell->t != NULL && shell->t[x] != '\0' && shell->t[x + 1]
			== '$' && x != 1)
			shell->t = re_ptit_bidule(shell, x);
		shell->t = ptit_bout_d_free(shell, x, y);
	}
	if (shell->t == NULL)
		shell->fre = 1;
	return (shell->t);
}

char	*dollar(char *str, t_mimi *shell, int x)
{
	shell->vent = 0;
	shell->tmp = NULL;
	shell->t = str;
	printf("dollar = str = %s\n", str);
	if (shell->t == shell->line)
		shell->same = 1;
	shell->size = ft_strlenn(shell->t);
	while (shell->fre != 1 && (shell->t && shell->t[x] != '\0'))
	{
		if (shell->t[x] == '$')
		{
			x++;
			doll(shell, x);
			x = 0;
		}
		else
			dol_else(shell, x);
		x = 0;
	}
	printf("doll fin tmp = %s\n", shell->tmp);
	return (dol_fin(shell));
}

///////////////////////////////////////////////////////////////////////////////

char	*dollary(char*str, t_mimi *shell, int x)
{
	int		y;
	char	*copy;

	shell->tmp = NULL;
	shell->t = str;
	printf("str = %s\n", shell->t);
	while (shell->t && shell->t[x] != '\0')
	{
		y = 0;
		if (shell->t[x] == '$')
		{
			printf("XXXXXXxx, %s\n",shell->t);
			x++;
			while ((ft_is_nb(shell->t[x + y]) == 1 || ft_is_alpha(shell->t[x + y])
					== 1 || shell->t[x + y] == '_') && shell->t[x + y] != '\0')
					y++;
			if (ft_is_nb(shell->t[x]) == 1 && y == 0)
			{
				//shell->tmp = joi(shell->tmp);
				shell->tmp = joi(shell->tmp, cpy_from_two_pos(shell->t, 0, x - 1));
				y++;//
				//dolly(shell, x);
			}
			else if (shell->t[x] == '?')
			{
				//shell->tmp = joi(shell->tmp, cftp(shell, 0, x - 1));
				shell->tmp = joi(shell->tmp, ft_itoaa(g_ret));
				y++;
				//printf("y = %d\n", y);
			}
			else if (y == 0)
			{
				shell->tmp = join(shell->tmp, malicious("$"));
				y = 0;
			}
			else
			{
				printf("ENTRE\n");
				//while ((ft_is_nb(shell->t[x + y]) == 1 || ft_is_alpha(shell->t[x + y])
			//		== 1 || shell->t[x + y] == '_') && shell->t[x + y] != '\0')
			//		y++;
				//printf("x = %d,y = %d\n",x, y);
				shell->tmp = joi(shell->tmp, cpy_from_two_pos(shell->t, 0, x - 1));
				//printf("test mp = %s\n", shell->tmp);
				shell->f_env = find_env(cftp(shell, x, x + y), shell);
				//printf("f env = %s\n", shell->f_env);
				if (shell->f_env != NULL)
					shell->tmp = joi(shell->tmp, shell->f_env);
				
			}
			printf("cut ici %s\n", shell->t);
			copy = ft_strdup(shell->t);
			free(shell->t);
			shell->t = cut_i(copy, x + y);
			free(copy);
		//	printf("str = %s, tmp = %s\n", shell->t, shell->tmp);
			x = -1;
		}
		else
		{
			printf("passe\n");
			shell->tmp = joi(shell->tmp, cpy_from_two_pos(shell->t, 0, x + 1));
			copy = ft_strdup(shell->t);
			free(shell->t);
			shell->t = cut_i(copy, x + 1);
			free(copy);
			x = -1;
		}
		printf("fin de boucle tmp = %s, line =  %s\n", shell->tmp, shell->t);
		x++;
	}
	return (shell->tmp);

}
//"$USER.$USER"tmp$? $?
