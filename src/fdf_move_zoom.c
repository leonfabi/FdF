/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_move_zoom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:04:41 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 09:39:59 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_move_hook(void *param)
{
	t_mc	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
	{
		fdf->y_trans -= 10;
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
	{
		fdf->y_trans += 10;
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
	{
		fdf->x_trans -= 10;
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
	{
		fdf->x_trans += 10;
		ft_draw_grid(fdf, fdf->img);
	}
}

void	ft_zoom(t_mc *fdf)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			fdf->data[y][x].z_proj = fdf->zoom * \
			fdf->data[y][x].z_proj;
			fdf->data[y][x].y_proj = fdf->zoom * \
			fdf->data[y][x].y_proj;
			fdf->data[y][x].x_proj = fdf->zoom * \
			fdf->data[y][x].x_proj;
			fdf->data[y][x].x_draw = round(fdf->data[y][x].x_proj);
			fdf->data[y][x].y_draw = round(fdf->data[y][x].y_proj);
			x++;
		}
		y++;
	}
	fdf->zoom = 1;
}

void	ft_zoom_hook(void *param)
{
	t_mc	*fdf;
	int		y;
	int		x;

	y = 0;
	x = 0;
	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		fdf->zoom += 0.1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
	{
		fdf->zoom -= 0.1;
	}
	ft_zoom(fdf);
	ft_draw_grid(fdf, fdf->img);
}
