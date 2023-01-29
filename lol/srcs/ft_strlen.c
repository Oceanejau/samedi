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

size_t	ft_strlen(const char *s)
{
	unsigned int	size;

	size = 0;
	if (s == NULL || s[0] == '\0')
		return (size);
	while (s[size] != '\0')
		size++;
	return (size);
}
