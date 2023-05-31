/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:57:26 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/31 15:57:51 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_2d(char **tmp)
{
	int	count;

	count = 0;
	if (tmp != NULL)
	{
		while (tmp[count])
			free(tmp[count++]);
		free(tmp);
	}
}