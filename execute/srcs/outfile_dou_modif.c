/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_dou_modif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:54:03 by wmari             #+#    #+#             */
/*   Updated: 2023/01/31 12:34:43 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	outfile_dou_modif(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (perror(file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
