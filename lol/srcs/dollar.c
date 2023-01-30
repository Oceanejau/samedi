#include "minishell.h"

int	str_c(char *str, char c)
{
	int	x;

	x = 0;
	//printf("str_c cccccccc, |%s|, |%c|\n", str, c);
	if (c == '\0')
		return (7);
	while (str[x] != '\0')
	{
		if (str[x] == c)
		{
		//	printf("sort ici, c = -%c-, x = %d\n", str[x], x);
			return (x);
		}
		x++;
	}
//	printf("else\n");
	return (10);
}

int	find_doll(char *str, int x)
{
	int	y;

	y = 0;
	if (str[x + 1] == '\0')
		return (0);
	else if (str[x + 1] == '?' || str[x + 1] == '$')
	    return (-1);// return (ft_itoa((int)getpid());)
	else if (str[x + 1] == '"')
		return (x - next_kote(str, str[x + 1], x + 1));
	while (str[x + y] != '\0' && (ft_is_nb(str[x + y]) == 1 || ft_is_alpha(str[x + y]) == 1 || str[x + y] == '_'))
		y++;
	return (y);
}

char *redoll(char *str, t_mimi *shell, int x)
{
	char	*tmp;
	int		size;

	tmp = NULL;
	if (x > 0)
		tmp = join(tmp, cpy_from_two_pos(str, 0, x));
	size = find_doll(str, x);
	if (size > 0)
		tmp = join(tmp, find_env(cpy_from_two_pos(str, x, x + size), shell));
	else if (size == -1 && str[x + 1] == '?')
		tmp = join(tmp, ft_itoa(shell->ret));
	else if (size == -1 && str[x + 1] == '$')
		tmp = join(tmp, ft_itoa((int)getpid()));//a voir si on peut faire ca
	else if (size == 0)
		tmp = join(tmp, "$");
//	printf("fin redoll, %s, %d\n", tmp, size);
	return (tmp);
}

char	*dollary(char *str, t_mimi *shell, int x)
{
	char	*tmp;
	int		y;
//	char	*str;
	char *copy;

	tmp = NULL;

	//str = cpy_from_two_pos(strr, 0, ft_strlenn(strr));
//	free(strr);
	shell->size = ft_strlenn(str);
	shell->s = ft_strlenn(shell->line);
	while (str && ft_strlenn(str) > 0 && (str[x] && str[x] != '\0'))
	{
		printf("debut -- str = %s, tmp =%s\n", str, tmp);
		if (str[x] == '$')
		{
			//	printf("x = %d dollar trouve ici\n", x);
			x++;
			y = 0;
			if (ft_is_nb(str[x]) == 1)
			{
				if (x > 1)
					tmp = join(tmp, cpy_from_two_pos(str, 0, x - 1));
				copy = ft_strdup(str);
				free(str);
				str = cut_in(copy, x + 1);//malloc ici et perdu ensuite
				free(copy);
				// str = cut_in(str, x + 1);
			//	printf("Cetait des chiffres tmp =-%s-, str = -%s-\n",tmp, str);/////////////////////////
			}
			else if (ft_is_nb(str[x]) != 1)
			{
				while ((ft_is_nb(str[x + y]) == 1 || ft_is_alpha(str[x + y]) == 1 || str[x + y] == '_') && str[x + y] != '\0')
					y++;
				if (y == 0 && str[x + y] == '?')
				{
					tmp = join(tmp, cpy_from_two_pos(str, 0, x - 1));
//printf("$? = str = -%s- tmp = -%s- line = -%s- x = %d\n", str, tmp, shell->line, x);
					tmp = join(tmp, ft_itoaa(g_ret));
					// str = join(NULL, cut_in(str, x + y + 1));
				//	printf("tmp = %s, str %s\n", tmp, str);
				}
				else if (str && str[x + y] != '\0' && str[x + y] != '$' && str_c(shell->instr, str[x + y]) == 10)
					return (char_err("something went wrong with this variable", 2));
				else if (y == 0)
					return (join(tmp, malicious("$")));
			//	printf("BEFORE\n");
				//tmp = join(tmp, cpy_from_two_pos(str, 0, x - 1));
				printf("==========tmp = %s, str = %s\n", tmp, str);
				tmp = join(tmp, find_env(cpy_from_two_pos(str, x, x + y), shell));
				if (str != NULL && str[x + 1] == '$')
				{
					printf("BEF = %s\n", str);
					copy = ft_strdup(str);
				free(str);
				str = cut_in(copy, x);//malloc ici et perdu ensuite
				free(copy);
					// str = cut_in(str, x);
					printf("NEXT = %s\n", str);
					shell->s = 1;
				}
				printf("STR1 = -%s\n", str);

				copy = ft_strdup(str);
				free(str);
				str = cut_in(copy, x + y);//malloc ici et perdu ensuite
				free(copy);


			//	str = cpy_from_two_posi(shell, str, x + y, ft_strlenn(str));
			//	free(str);
			//	str = strr;
				if (str == NULL && shell->size == shell->s)
				{
					free(shell->line);
					shell->line = NULL;
				}
				printf("STR2 = -%s\n", str);
			}
			x = 0;
			//	printf("YYYY tmp == %s, str = %s, %d\n", tmp, str, x);
		}
		else
		{
			printf("JOIN\n");
			tmp = join(tmp, cpy_from_two_pos(str, 0, x + 1));
			copy = ft_strdup(str);
				free(str);
				str = cut_in(copy, x + 1);//malloc ici et perdu ensuite
				free(copy);
			// str = cut_in(str, x + 1);
		//	printf("Passe dans le foutu join, tmp = %s, str %s\n", tmp, str);
		}
	//	printf("else\n");
	//	printf(" %d -%s- -%s-\n", x, str, tmp);
		if (str)
		{
			// printf("dollar:before join:str=%p\n", str);
			// // str = join(NULL, cpy_from_two_pos(str, x, ft_strlenn(str)));
			// printf("dollar:after join:str=%p\n", str);
			// printf("rentre dan if\n");
		}
		//printf("str =================== %s, %s\n", str, tmp);
		x = 0;
	}
	//	printf("iDOLLAR     tmp = -%s- line = -%s- str = -%s-\n", tmp, shell->line, str);
	shell->size = shell->size - ft_strlenn(str);
	printf("size == %d\n", shell->size);
	free(str);
	return (tmp);
}
