/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:46:32 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 15:21:51 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_isometric_calculation(t_mc *fdf, int y, int x, double rad)
{
	double	x_pr;
	double	y_pr;
	double	z_pr;

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
}

void	ft_to_isometric(t_mc *fdf)
{
	double	rad;
	int		y;
	int		x;

	rad = -M_PI / 4;
	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			ft_isometric_calculation(fdf, y, x, rad);
			x++;
		}
		y++;
	}
	ft_draw_grid(fdf, fdf->img);
}

void	ft_to_xy(t_mc *fdf)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			fdf->data[y][x].x_proj = SCALING * fdf->data[y][x].x;
			fdf->data[y][x].y_proj = SCALING * fdf->data[y][x].y;
			fdf->data[y][x].z_proj = SCALING * fdf->data[y][x].z;
			fdf->data[y][x].x_draw = fdf->data[y][x].x_proj;
			fdf->data[y][x].y_draw = fdf->data[y][x].y_proj;
			x++;
		}
		y++;
	}
	ft_draw_grid(fdf, fdf->img);
}

void	ft_to_yz(t_mc *fdf)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			fdf->data[y][x].x_proj = SCALING * fdf->data[y][x].x;
			fdf->data[y][x].y_proj = (-1) * SCALING * fdf->data[y][x].z;
			fdf->data[y][x].z_proj = SCALING * fdf->data[y][x].y;
			fdf->data[y][x].x_draw = fdf->data[y][x].x_proj;
			fdf->data[y][x].y_draw = fdf->data[y][x].y_proj;
			x++;
		}
		y++;
	}
	ft_draw_grid(fdf, fdf->img);
}
