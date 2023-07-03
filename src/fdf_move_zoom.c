/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_move_zoom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:04:41 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/03 14:29:58 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_move(t_mc *fdf, int mode)
{
	if (mode == 1)
		fdf->y_trans -= 10;
	else if (mode == 2)
		fdf->y_trans += 10;
	else if (mode == 3)
		fdf->x_trans -= 10;
	else if (mode == 4)
		fdf->x_trans += 10;
	ft_draw_grid(fdf, fdf->img);
}

void	ft_move_hook(void *param)
{
	t_mc	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_8) || \
	mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		ft_move(fdf, 1);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_5) || \
	mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		ft_move(fdf, 2);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_4) || \
	mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		ft_move(fdf, 3);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_6) || \
	mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		ft_move(fdf, 4);
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

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
	{
		fdf->zoom += 0.03;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT))
	{
		fdf->zoom -= 0.03;
	}
	ft_zoom(fdf);
	ft_draw_grid(fdf, fdf->img);
}
