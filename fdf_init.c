/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:47:23 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 09:23:52 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_init(t_mc *fdf)
{
	fdf->input = NULL;
	fdf->x_len = 0;
	fdf->y_len = 0;
	fdf->img = NULL;
	fdf->x_trans = WIDTH / 3;
	fdf->y_trans = HEIGHT / 3;
	fdf->zoom = 1;
	fdf->max = 0;
	fdf->min = 0;
	// fdf->draw = (t_ld )malloc(sizeof(t_ld));
	// if (fdf->draw == NULL)
	// {
	// 	free(fdf->draw);
	// 	fdf->draw = NULL;
	// 	return (-1);
	// }
	fdf->draw.dx = 0;
	fdf->draw.dy = 0;
	fdf->draw.err = 0;
	fdf->draw.sx = 0;
	fdf->draw.sy = 0;
	fdf->draw.e = 0;
	return (1);
}

int	ft_init_data(t_mc *fdf)
{
	int	y_size;

	y_size = 0;
	fdf->data = (t_point **)malloc(sizeof(t_point *) * fdf->y_len);
	if (fdf->data == NULL)
	{
		free(fdf->data);
		fdf->data = NULL;
		return (-1);
	}
	while (y_size < fdf->y_len)
	{
		fdf->data[y_size] = malloc(sizeof(t_point) * fdf->x_len);
		if (fdf->data[y_size] == NULL)
		{
			ft_free_data(fdf->data, y_size);
			return (-1);
		}
		y_size++;
	}
	return (1);
}
