/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_modif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:36:11 by wmari             #+#    #+#             */
/*   Updated: 2023/02/07 19:33:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	outfile_modif(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0666);
	if (fd == -1)
		return (perror(file), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror(file), close(fd), 1);
	close(fd);
	return (0);
}
