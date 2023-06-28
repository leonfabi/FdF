/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:46:32 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 09:46:45 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_to_isometric(t_mc *fdf)
{
	double	x_pr;
	double	y_pr;
	double	z_pr;
	double	rad;
	int	y;
	int	x;

	rad = -M_PI / 4;
	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			x_pr = SCALING * fdf->data[y][x].x;
			y_pr = SCALING * fdf->data[y][x].y;
			z_pr = SCALING * fdf->data[y][x].z;
			rad = -M_PI / 4;
			fdf->data[y][x].x_proj = round(cos(rad) * x_pr + sin(rad) * y_pr);
			y_pr = round(cos(rad) * y_pr - sin(rad) * x_pr);
			rad = M_PI / 180 * -35.264;
			fdf->data[y][x].y_proj = round(cos(rad) * y_pr + sin(rad) * z_pr);
			fdf->data[y][x].z_proj = round(cos(rad) * z_pr - sin(rad) * y_pr);
			fdf->data[y][x].x_draw = fdf->data[y][x].x_proj;
			fdf->data[y][x].y_draw = fdf->data[y][x].y_proj;
			x++;
		}
		y++;
	}
	ft_draw_grid(fdf, fdf->img);
}

void	ft_to_oblique(t_mc *fdf)
{
	double	x_pr;
	double	y_pr;
	double	z_pr;
	double	rad;
	int	y;
	int	x;

	rad = M_PI / 4 * 2;
	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			x_pr = SCALING * fdf->data[y][x].x;
			y_pr = SCALING * fdf->data[y][x].y;
			z_pr = SCALING * fdf->data[y][x].z;
			rad = -M_PI / 4;
			fdf->data[y][x].x_proj = x_pr;//round(- cos(rad) * z_pr * 0.5 + x_pr);
			fdf->data[y][x].y_proj = y_pr;//round(- sin(rad) * z_pr * 0.5 + y_pr);
			fdf->data[y][x].z_proj = z_pr;
			fdf->data[y][x].x_draw = fdf->data[y][x].x_proj;
			fdf->data[y][x].y_draw = fdf->data[y][x].y_proj;
			x++;
		}
		y++;
	}
	ft_draw_grid(fdf, fdf->img);
}