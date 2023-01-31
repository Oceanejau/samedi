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

	x = 0;
	y = 0;
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s2);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (char_err("failed to allocate memory", 2));
	while (s1[x] != '\0')
	{
		tmp[x] = s1[x];
		x++;
	}
	while (s2[y] != '\0')
	{
		tmp[x + y] = s2[y];
		y++;
	}
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

size_t	ft_memlen(void *s)
{
	unsigned int	size;
	unsigned char	*str;

	size = 0;
	str = (unsigned char *)s;
	while (str[size] != '\0')
		size = size + 1;
	return (size);
}

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned int	i;
	unsigned char	*dest;
	unsigned char	*source;

	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (dst);
	while (i < (unsigned int)size && (unsigned int)size > 0)
	{
		dest[i] = source[i];
		i = i + 1;
	}
	dest[i] = '\0';
	return (dest);
}
/*
char	*do_big_quote(t_mimi *shell, int x)
{
	//on reparcours la chaine si c'est un double quote et on modifie les $ sinon rien
	//on stock dans un int de la structure la taille de ce que l'on a copie pour reparcourir apres uniquement les nouveaux elelments
	// ici on ret tmp on go dans big quote et on cherche d'autres quotes ' ou " ou des white spaces etc if on trouve des quotes on les gere
	char	*tmpp;
	char	*tmp;

	shell->ferme = 1;
	while (shell->line != NULL && str_c(shell->instr, shell->line[x]) >= 2
		&& shell->line[x] != '\0')
	{
		if (x > 0)
			tmp = get_in(shell->line, x);
		shell->line = cut_in(shell->line, x + 1);
		if (str_c(shell->instr, shell->line[x]) >= 2)
		{
			if (shell->ferme == 0)
				shell->ferme--;
			else
				shell->ferme++;
			tmpp = do_quote(shell, x, shell->line[x]);
			tmp = johnny(tmp, tmpp);
	//		printf("tenter un truc -------------------%s-\n", tmp);
		}
		x++;
	}*/
/*	tmp = johnny(tmp, get_in(shell->line, x));
	shell->line = cut_in(shell->line, x);*/
//	printf("Fin de big quote str = -%s-\n", tmp);
	/*return (tmp);
}*/

int	check_for_quotes(t_mimi *shell, char c)
{
	int	x;

	x = 0;
	while (shell->line[x] != '\0' && str_c(shell->instr, shell->line[x]) >= 2)
	{
		if (str_c(shell->instr, shell->line[x]) >= 2 && shell->line[x] != c && shell->ferme == 1)
		{
	//		printf("fais un truc\n");
			return (x);
		}
		x++;
	}
	return (x);
}

char	*do_quote(t_mimi *shell, int x, char c)
{
	char	*tmp;

	tmp = NULL;
/*	if (x > 0)
		tmp = get_in(shell->line, x);
	shell->line = cut_in(shell->line, x + 1);*/
	//printf("tmp = -%s-\n", tmp);
	if (shell->line == NULL)
	{
		printf("error manque une quote %c\n", c);
		exit (-1);
	}
	x = where_is_charly(shell->line, 0, c);
	x = check_for_quotes(shell, c);
//	printf("str = %s x = %d\n", shell->line, x);
	/*
	 * if(x == -1)
	 * error de quote
	 * return ();
	 * */
	if (x < 0)
	{
		printf("error manque une quote %c\n", c);
		exit (-1);
	}
	tmp = johnny(tmp, get_in(shell->line, x));
	shell->line = cut_in(shell->line, x + 1);
	return (tmp);
/*	x = 0;
	while (shell->line != NULL && str_c(shell->instr, shell->line[x]) >= 2
		&& shell->line[x] != '\0')
		x++;
	tmp = johnny(tmp, get_in(shell->line, x));
	shell->line = cut_in(shell->line, x);
	printf("Fin de quote str = -%s-\n", tmp);
	return (tmp);*/
}

t_list	*ft_listnew(char *content, int x)
{
	t_list			*newblock;
	unsigned int	size;

	newblock = (t_list *)malloc(sizeof(*newblock));
	if (!newblock)
		return ((t_list *)char_err("failed to allocate memory", 2));
	if (content == NULL)
	{
		newblock->str = NULL;
		newblock->next = NULL;
		return (newblock);
	}
	size = ft_memlen(content);
	newblock->str = (char *)malloc(sizeof(char) * size + 1);
	newblock->type = x;
	if (!newblock->str)
		return ((t_list *)char_err("failed to allocate memory", 2));
	ft_memcpy(newblock->str, content, size);
	newblock->next = NULL;
	return (newblock);
}

void	ft_listadd_back(t_list **alst, t_list *new)
{
	t_list *blist;

	if (alst && new)
	{
		blist = (*alst);
		if (blist == NULL)
			(*alst = new);
		else
		{
			while (blist->next)
				blist = blist->next;
			blist->next = new;
		}
	}
}

/*char	pad(char *s, int x)
{
	char	*copy;
	int		i;

	i = 0;
	if (s != NULL)
	{
		copy = s;
		while (*copy != '\0' && i < x)
			copy++;
	}
	if (i == x)
		return (*copy);
	return (0);
}*/

int	mani(t_mimi *shell)
{
	char	*str;
	int		x;
//	char	*tmp;

	str = NULL;
//	tmp = shell->line;
	shell->quote = 0;
	shell->nb_hd = 0;
	x = 0;
	//printf("MANI= -%s-\n", shell->line);

	while (shell->line != NULL && /*pad(shell->line, x)*/shell->line[x] != '\0')
	{
	//	printf("PAS NUL x = %d\n", x);
		
		if (str_c(shell->instr, /*pad(shell->line, x)*/shell->line[x]) != 10
			|| shell->line[x + 1] == '\0')
		{
			str = repartiteur(shell, x, str);
			x = -1;
		//	printf("strrrrr = -%s-, -%s-, -%s-\n", str, shell->line, tmp);
			if (str == NULL && shell->ret == -1)
			{
				//printf("PASSE\n");
				free_list(shell);
				free(shell->line);
				free(str);
			}
			else if (str != NULL && ft_strlen(str) != 0)// && str[0] != '\0')//// else ++
			{
			//	printf("str = %s, %d\n", str, shell->type);
				ft_listadd_back(&shell->list, ft_listnew(str, shell->type));
				// if (str[0] == 'e' && str[1] == 'x' && str[2] == 'i'
				// 	&& str[3] == 't' && str[4] == '\0')
				// 	exit(1);//return la derniere valeur de return!!!!!!!!!!!!!!1
				free(str);
			}
		}
	//	tmp = shell->line;
	//	printf("ree\n");
		//free(shell->line);
		x++;
	}
	return (0);
}
