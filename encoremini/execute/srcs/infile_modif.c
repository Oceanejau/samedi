/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:13:28 by wmari             #+#    #+#             */
/*   Updated: 2022/12/19 17:09:28 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	infile_modif(char *file, int fd)
{
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
