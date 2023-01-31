#include "minishell.h"

char	*dol_else(t_mimi *shell, char *str, int x)
{
	char	*copy;

	if (str != NULL)
	{
		shell->tmp = joi(shell->tmp, cpy_from_two_posi(str, 0, x + 1));
		copy = ft_strdup(str);
		///free(str);//
		str = cut_i(copy, x + 1);
		free(copy);
	}
	else
		return (NULL);
	return (str);
}

char	*ptit_bidule(t_mimi *shell, char *str, int x)
{
	shell->tmp = joi(shell->tmp, cpy_from_two_posi(str, 0, x - 1));
	shell->tmp = joi(shell->tmp, ft_itoaa(g_ret));
	return (shell->tmp);
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

char	*dol_fin(t_mimi *shell, char *str)
{
	shell->size = shell->size - ft_strlenn(str);
	free(str);
	return (shell->tmp);
}

char	*ptit_bout_d_free(t_mimi *shell, char *str, int x, int y)
{
	char	*copy;

	copy = ft_strdup(str);
	free(str);
	str = cut_i(copy, x + y);
	free(copy);
	if (str == NULL && shell->size == shell->s)
		ptit_free(shell);
	return (str);
}

char	*bb_mid(t_mimi *shell, char *str, int x, int y)
{
	if (y == 0 && str[x + y] == '?')
		shell->tmp = ptit_bidule(shell, str, x);
	else if (str && str[x + y] != '\0' && str[x + y] != '$'
		&& str_c(shell->instr, str[x + y]) == 10)
		return (char_err("something went wrong with this variable", 2));
	else if (y == 0)
		shell->tmp = joi(shell->tmp, malicious("$"));
	shell->tmp = joi(shell->tmp, find_env(cpy_from_two_posi(str, x, x + y),
				shell));
	return (shell->tmp);
}

char	*doll(t_mimi *shell, char *str, int x)
{
	int		y;
	char	*copy;

	y = 0;
	if (ft_is_nb(str[x]) == 1)
	{
		if (x > 1)
			shell->tmp = joi(shell->tmp, cpy_from_two_posi(str, 0, x - 1));
		copy = ft_strdup(str);
		free(str);
		str = cut_i(copy, x + 1);
		free(copy);
	}
	else if (ft_is_nb(str[x]) != 1)
	{
		while ((ft_is_nb(str[x + y]) == 1 || ft_is_alpha(str[x + y]) == 1
				|| str[x + y] == '_') && str[x + y] != '\0')
			y++;
		shell->tmp = bb_mid(shell, str, x, y);
		if (str != NULL && str[x] != '\0' && str[x + 1] == '$')
			str = re_ptit_bidule(str, shell, x);
		str = ptit_bout_d_free(shell, str, x, y);
	}
	return (str);
}

char	*dollary(char *str, t_mimi *shell, int x)
{
	shell->tmp = NULL;
	shell->size = ft_strlenn(str);
	shell->s = ft_strlenn(shell->line);
	while (str && ft_strlenn(str) > 0 && (str[x] && str[x] != '\0'))
	{
		if (str[x] == '$')
		{
			x++;
			doll(shell, str, x);
			x = 0;
		}
		else
			dol_else(shell, str, x);
		x = 0;
	}
	return (dol_fin(shell, str));
}
