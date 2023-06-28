/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:43:03 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 16:41:24 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	ft_color(int z, t_mc *fdf)
{
	int	norm;

	norm = (z - fdf->min) / (fdf->max - fdf->min) * 6 * 256;
	if (norm >= 5 * 256)
		return (get_rgba(255, 0, 255 - (norm - 5 * 256), 255));
	else if (norm >= 4 * 256)
		return (get_rgba((norm - 4 * 256), 0, 0, 255));
	else if (norm >= 3 * 256)
		return (get_rgba(0, 255 - (norm - 3 * 256), 255, 255));
	else if (norm >= 2 * 256)
		return (get_rgba(0, 255, (norm - 2 * 256), 255));
	else if (norm >= 256)
		return (get_rgba(255 - (norm - 256), 255, 0, 255));
	else
		return (get_rgba(255, norm, 0, 255));
}

