/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:57:29 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:57:46 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

size_t	ft_strlenn(const char *s)
{
	unsigned int	size;

	size = 0;
//	printf("s = %s\n", s);
	if (!s)
		return (size);
	while (s && s[size] != '\0')
		size++;
	//printf("size = %d\n", size);
	return (size);
}
