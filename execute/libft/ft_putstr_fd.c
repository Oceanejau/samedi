/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@42.student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:29:54 by wmari             #+#    #+#             */
/*   Updated: 2020/12/08 11:03:39 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	*copy;

	if (s != NULL)
	{
		copy = s;
		while (*copy != '\0')
		{
			ft_putchar_fd(*copy, fd);
			copy++;
		}
	}
}
