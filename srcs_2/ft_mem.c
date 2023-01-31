/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 06:53:11 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/31 06:53:14 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
