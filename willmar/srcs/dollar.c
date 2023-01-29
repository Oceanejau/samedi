#include "minishell.h"

int	str_c(char *str, char c)
{
	int	x;

	x = 0;
	if (c == '\0')
		return (7);
	while (str[x] != '\0')
	{
		if (str[x] == c)
		{
		//	printf("sort ici, c = -%c-\n", str[x]);
			return (x);
		}
		x++;
	}
	return (10);
}

/*char	*doll_point(t_mimi *shell, char *str)
{
	
	return (ft_itoa(shell->ret));
}*/
//$! ne renvoie rien
int	find_doll(char *str, int x)
{
	//char	*tmp;
	//int		size;
	int	y;

	y = 0;
	/*si ca commence par un chiffre*/
	if (str[x + 1] == '\0')
		return (0);
	else if (str[x + 1] == '?' || str[x + 1] == '$')
	    return (-1);// return (ft_itoa((int)getpid());)
	else if (str[x + 1] == '"')
		return (x - next_kote(str, str[x + 1], x + 1));// a verifier
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
		/*
		 * $? a faire a la mano dans la struct
		 *
		 *
		 */
		char	*tmp;
		int		y;
//return (NULL);
		//	return (redoll(str, shell, x));
	//		printf("DOLLAR -%s- %d -%s-\n", str, x, shell->line);
		/*	if (ft_strlen(str) == 2 && str[1] == '?')
			{
		//printf("RET %d\n", shell->ret);
		return (ft_itoa(shell->ret));
		}*/
		tmp = NULL;
		shell->size = ft_strlen(str);
		while (str && ft_strlen(str) > 0 && str[x] != '\0')
		{
				//printf("debut -- str = %s, tmp =%s\n", str, tmp);
				if (str[x] == '$')
				{
					//	printf("x = %d dollar trouve ici\n", x);
					x++;
					y = 0;
					if (ft_is_nb(str[x]) == 1)
					{
						if (x > 1)
							tmp = join(tmp, cpy_from_two_pos(str, 0, x - 1));
						str = cut_in(str, x + 1);
					//	printf("Cetait des chiffres tmp =-%s-, str = -%s-\n",tmp, str);/////////////////////////
					}
					else if (ft_is_nb(str[x]) != 1)
					{
						while ((ft_is_nb(str[x + y]) == 1 || ft_is_alpha(str[x + y]) == 1 || str[x + y] == '_') && str[x + y] != '\0')
							y++;
						if (y == 0 && str[x + y] == '?')
						{
				//			printf("$?\n");
							tmp = join(tmp, cpy_from_two_pos(str, 0, x - 1));
							tmp = join(tmp, ft_itoa(shell->ret));
							str = cut_in(str, x + y + 1);
				//			printf("tmp = %s, str %s\n", tmp, str);
						}
								//printf("YYYYYYYYYYYY = %d\n", y);
								/*if (y == 0 && str[x + 1] == '"')//ici on gere les quotes
								  {
								  return (ft_itoa(shell->ret));
								  }
								  */if (str[x + y] != '\0' && str[x + y] != '$' && str_c(shell->instr, str[x + y]) == 10)
									return (char_err("something went wrong with this variable", 2));
								else if (y == 0)
								{
										//	printf("emmtre\n");
										//tmp = join(tmp, "$");
										return (join(tmp, malicious("$")));
										//	printf("tmp = %s\n", tmp);
										shell->s = 1;
								}
								//	printf("BEFORE\n");
								tmp = join(tmp, cpy_from_two_pos(str, 0, x - 1));
								//printf("==========tmp = %s, str = %s\n", tmp, str);
								tmp = join(tmp, find_env(cpy_from_two_pos(str, x, x + y), shell));
								if (str != NULL && str[x + 1] == '$')
								{
										//	tmp = join(tmp, "1371615");
										shell->s = 1;
								}
								str = cut_in(str, x + y);
						}
						x = 0;
						//	printf("YYYY tmp == %s, str = %s, %d\n", tmp, str, x);
				}
				else
				{
		//			printf("JOIN\n");
					tmp = join(tmp, cpy_from_two_pos(str, 0, x + 1));
					str = cut_in(str, x + 1);
					//printf("Passe dans le foutu join, tmp = %s, str %s\n", tmp, str);
				}
			//	printf("else\n");
			//	printf(" %d -%s- -%s-\n", x, str, tmp);
				if (str)
				{
					str = join(NULL, cpy_from_two_pos(str, x, ft_strlen(str)));
			//		printf("rentre dan if\n");
				}
				//printf("str =================== %s, %s\n", str, tmp);
				x = 0;
		}
	//	printf("iDOLLAR     tmp = -%s- line = -%s- str = -%s-\n", tmp, shell->line, str);
		shell->size = shell->size - ft_strlen(str);

		if (str == NULL)
		{
			free(str);
		//	shell->line = NULL;
		}
		//	free(str);///
	//	printf("size = %d\n", shell->size);
		return (tmp);
}
