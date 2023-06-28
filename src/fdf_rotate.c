/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:48:37 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 16:21:22 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(t_mc *fdf)
{
	double	y_old;
	double	z_old;
	double	alpha;
	int		y;
	int		x;

	y = 0;
	x = 0;
	alpha = M_PI / 180 * 1;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			z_old = fdf->data[y][x].z_proj;
			y_old = fdf->data[y][x].y_proj;
			fdf->data[y][x].z_proj = cos(alpha) * z_old - sin(alpha) * y_old;
			fdf->data[y][x].y_proj = cos(alpha) * y_old + sin(alpha) * z_old;
			fdf->data[y][x].x_draw = round(fdf->data[y][x].x_proj);
			fdf->data[y][x].y_draw = round(fdf->data[y][x].y_proj);
			x++;
		}
		y++;
	}
}

void	ft_rotate_y(t_mc *fdf)
{
	double	x_old;
	double	z_old;
	double	alpha;
	int		y;
	int		x;

	y = 0;
	x = 0;
	alpha = M_PI / 180 * 1;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			z_old = fdf->data[y][x].z_proj;
			x_old = fdf->data[y][x].x_proj;
			fdf->data[y][x].z_proj = cos(alpha) * z_old + sin(alpha) * x_old;
			fdf->data[y][x].x_proj = cos(alpha) * x_old - sin(alpha) * z_old;
			fdf->data[y][x].x_draw = round(fdf->data[y][x].x_proj);
			fdf->data[y][x].y_draw = round(fdf->data[y][x].y_proj);
			x++;
		}
		y++;
	}
}

void	ft_rotate_z(t_mc *fdf)
{
	double	x_old;
	double	y_old;
	double	alpha;
	int		y;
	int		x;

	y = 0;
	x = 0;
	alpha = M_PI / 180 * 1;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			x_old = fdf->data[y][x].x_proj;
			y_old = fdf->data[y][x].y_proj;
			fdf->data[y][x].x_proj = cos(alpha) * x_old + sin(alpha) * y_old;
			fdf->data[y][x].y_proj = cos(alpha) * y_old - sin(alpha) * x_old;
			fdf->data[y][x].x_draw = round(fdf->data[y][x].x_proj);
			fdf->data[y][x].y_draw = round(fdf->data[y][x].y_proj);
			x++;
		}
		y++;
	}
}

void	ft_rotate_hook(void *param)
{
	t_mc	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
	{
		ft_rotate_z(fdf);
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
	{
		ft_rotate_y(fdf);
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
	{
		ft_rotate_x(fdf);
		ft_draw_grid(fdf, fdf->img);
	}
}