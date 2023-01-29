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
		return (s1);
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
	if (s1)
		free(s1);
	if (s2)
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
	{
		free(newblock);
		return ((t_list *)char_err("failed to allocate memory", 2));
	}
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

int	mani(t_mimi *shell)
{
	char	*str;
	int		x;

	str = NULL;
	shell->quote = 0;
	shell->nb_hd = 0;
	x = 0;
	//printf("MANI= -%s-\n", shell->line);
	while (shell->line != NULL && shell->line[x] != '\0')
	{
		//printf("PAS NUL\n");
		if (str_c(shell->instr, shell->line[x]) != 10
			|| shell->line[x + 1] == '\0')
		{
			str = repartiteur(shell, x, str);
			x = -1;
		//	printf("strrrrr = %s, %s\n", str, shell->line);
			if (str == NULL && shell->ret == -1)
			{
			//	printf("PASSE\n");
				free_list(shell);
				free(shell->line);
				shell->line = NULL;
				free(str);
				str = NULL;
			}
			if (str != NULL && str[0] != '\0')
			{
			//	printf("str = %s, %d\n", str, shell->type);
				ft_listadd_back(&shell->list, ft_listnew(str, shell->type));
				// if (str[0] == 'e' && str[1] == 'x' && str[2] == 'i'
				// 	&& str[3] == 't' && str[4] == '\0')
				// 	exit(1);//return la derniere valeur de return!!!!!!!!!!!!!!1
				free(str);
				str = NULL;
			}
		}
		//free(shell->line);
		x++;
	}
	return (0);
}
