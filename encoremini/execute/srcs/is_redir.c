/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:34:26 by wmari             #+#    #+#             */
/*   Updated: 2022/12/07 11:45:25 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	is_redir(char *str)
{
	if (ft_strncmp(">>", str, 2) == 0)
		return (D_OUTFILE);
	if (ft_strncmp(">", str, 1) == 0)
		return (OUTFILE);
	if (ft_strncmp("<<", str, 2) == 0)
		return (D_INFILE);
	if (ft_strncmp("<", str, 1) == 0)
		return (INFILE);
	return (NOT_REDIR);
}
