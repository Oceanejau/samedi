#include "minishell.h"

char	*dol_else(char *tmp, char *str, int x)
{
	char	*copy;

	if (str != NULL)
	{
		tmp = joi(tmp, cpy_from_two_posi(str, 0, x + 1));
		copy = ft_strdup(str);
	//	free(str);
		str = cut_i(copy, x + 1);
		free(copy);
	}
	else 
		return (NULL);
	return (str);
}

char	*ptit_bidule(char *tmp, char *str, int x)
{
	tmp = joi(tmp, cpy_from_two_posi(str, 0, x - 1));
	tmp = joi(tmp, ft_itoaa(g_ret));
	return (tmp);
}

char	*re_ptit_bidule(char *str, t_mimi *shell, int x)
{
	char	*copy;

	copy = ft_strdup(str);
	free(str);
	str = cut_i(copy, x);
	free(copy);
	shell->s = 1;
	return (str);
}


void	ptit_free(t_mimi *shell)
{
	free(shell->line);
	shell->line = NULL;
}

char	*dollary(char *str, t_mimi *shell, int x)
{
	char	*tmp;
	int		y;
	char *copy;

	tmp = NULL;
	shell->size = ft_strlenn(str);
	shell->s = ft_strlenn(shell->line);
	while (str && ft_strlenn(str) > 0 && (str[x] && str[x] != '\0'))
	{
		if (str[x] == '$')
		{
			x++;
			y = 0;
			if (ft_is_nb(str[x]) == 1)
			{
				if (x > 1)
					tmp = joi(tmp, cpy_from_two_posi(str, 0, x - 1));
				copy = ft_strdup(str);
				free(str);
				str = cut_i(copy, x + 1);
				free(copy);
			}
			else if (ft_is_nb(str[x]) != 1)
			{
				while ((ft_is_nb(str[x + y]) == 1 || ft_is_alpha(str[x + y]) == 1 || str[x + y] == '_') && str[x + y] != '\0')
					y++;
				if (y == 0 && str[x + y] == '?')
					ptit_bidule(tmp, str, x);
				else if (str && str[x + y] != '\0' && str[x + y] != '$' && str_c(shell->instr, str[x + y]) == 10)
					return (char_err("something went wrong with this variable", 2));
				else if (y == 0)
					tmp = joi(tmp, malicious("$"));
				tmp = joi(tmp, find_env(cpy_from_two_posi(str, x, x + y), shell));
				if (str != NULL && str[x] != '\0' && str[x + 1] == '$')
					re_ptit_bidule(str, shell, x);
				copy = ft_strdup(str);
				free(str);
				str = cut_i(copy, x + y);
				free(copy);
				if (str == NULL && shell->size == shell->s)
					ptit_free(shell);
			}
			x = 0;
		}
		else
			dol_else(tmp, str, x);
		x = 0;
	}
	shell->size = shell->size - ft_strlenn(str);
	free(str);
	return (tmp);
}
