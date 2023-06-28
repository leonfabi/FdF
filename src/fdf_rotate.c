/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:48:37 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 15:24:46 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(t_mc *fdf, int sign)
{
	double	y_old;
	double	z_old;
	double	alpha;
	int		y;
	int		x;

	y = 0;
	x = 0;
	alpha = M_PI / 180 * sign;
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

void	ft_rotate_y(t_mc *fdf, int sign)
{
	double	x_old;
	double	z_old;
	double	alpha;
	int		y;
	int		x;

	y = 0;
	x = 0;
	alpha = M_PI / 180 * sign;
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

void	ft_rotate_z(t_mc *fdf, int sign)
{
	double	x_old;
	double	y_old;
	double	alpha;
	int		y;
	int		x;

	y = 0;
	x = 0;
	alpha = M_PI / 180 * sign;
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

void	ft_rotate(t_mc *fdf, int axis, int direction)
{
	if (axis == 0)
		ft_rotate_z(fdf, direction);
	else if (axis == 1)
		ft_rotate_y(fdf, direction);
	else if (axis == 2)
		ft_rotate_x(fdf, direction);
	ft_draw_grid(fdf, fdf->img);
}

void	ft_rotate_hook(void *param)
{
	t_mc	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_3) && \
	mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
		ft_rotate(fdf, 0, -1);
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_3))
		ft_rotate(fdf, 0, 1);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_2) && \
	mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
		ft_rotate(fdf, 1, -1);
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_2))
		ft_rotate(fdf, 1, 1);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_1) && \
	mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
		ft_rotate(fdf, 2, -1);
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_1))
		ft_rotate(fdf, 2, 1);
}
