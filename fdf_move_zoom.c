/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_move_zoom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:04:41 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/21 14:07:10 by fkrug            ###   ########.fr       */
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
		fdf->y_trans -= 5;
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
	{
		fdf->y_trans += 5;
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
	{
		fdf->x_trans -= 5;
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
	{
		fdf->x_trans += 5;
		ft_draw_grid(fdf, fdf->img);
	}
}

void	ft_zoom_hook(void *param)
{
	t_mc	*fdf;
	t_list	*tmp;

	tmp = fdf->coord;
	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		fdf->zoom += 0.01;
		while (tmp)
		{
			((t_point *)tmp->c)->z_proj = fdf->zoom * \
			((t_point *)tmp->c)->z_proj;
			((t_point *)tmp->c)->y_proj = fdf->zoom * \
			((t_point *)tmp->c)->y_proj;
			((t_point *)tmp->c)->x_proj = fdf->zoom * \
			((t_point *)tmp->c)->x_proj;
			((t_point *)tmp->c)->x_draw = round(((t_point *)tmp->c)->x_proj);
			((t_point *)tmp->c)->y_draw = round(((t_point *)tmp->c)->y_proj);
			tmp = tmp->next;
		}
		ft_draw_grid(fdf, fdf->img);
	}
}
