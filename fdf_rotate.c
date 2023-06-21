/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ft_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:48:37 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/21 13:59:40 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(t_list *tmp)
{
	double	x_old;
	double	y_old;
	double	z_old;
	double	alpha;

	alpha = M_PI / 180 * 1;
	while (tmp)
	{
		z_old = ((t_point *)tmp->c)->z_proj;
		y_old = ((t_point *)tmp->c)->y_proj;
		((t_point *)tmp->c)->z_proj = cos(alpha) * z_old - sin(alpha) * y_old;
		((t_point *)tmp->c)->y_proj = cos(alpha) * y_old + sin(alpha) * z_old;
		((t_point *)tmp->c)->x_draw = round(((t_point *)tmp->c)->x_proj);
		((t_point *)tmp->c)->y_draw = round(((t_point *)tmp->c)->y_proj);
		tmp = tmp->next;
	}
}

void	ft_rotate_y(t_list *tmp)
{
	double	x_old;
	double	y_old;
	double	z_old;
	double	alpha;

	alpha = M_PI / 180 * 1;
	while (tmp)
	{
		z_old = ((t_point *)tmp->c)->z_proj;
		x_old = ((t_point *)tmp->c)->x_proj;
		((t_point *)tmp->c)->z_proj = cos(alpha) * z_old + sin(alpha) * x_old;
		((t_point *)tmp->c)->x_proj = cos(alpha) * x_old - sin(alpha) * z_old;
		((t_point *)tmp->c)->x_draw = round(((t_point *)tmp->c)->x_proj);
		((t_point *)tmp->c)->y_draw = round(((t_point *)tmp->c)->y_proj);
		tmp = tmp->next;
	}
}

void	ft_rotate_z(t_list *tmp)
{
	double	x_old;
	double	y_old;
	double	z_old;
	double	alpha;

	alpha = M_PI / 180 * 1;
	while (tmp)
	{
		x_old = ((t_point *)tmp->c)->x_proj;
		y_old = ((t_point *)tmp->c)->y_proj;
		((t_point *)tmp->c)->x_proj = cos(alpha) * x_old + sin(alpha) * y_old;
		((t_point *)tmp->c)->y_proj = cos(alpha) * y_old - sin(alpha) * x_old;
		((t_point *)tmp->c)->x_draw = round(((t_point *)tmp->c)->x_proj);
		((t_point *)tmp->c)->y_draw = round(((t_point *)tmp->c)->y_proj);
		tmp = tmp->next;
	}
}

void	ft_rotate_hook(void *param)
{
	t_mc	*fdf;
	t_list	*tmp;

	fdf = param;
	tmp = fdf->coord;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
	{
		ft_rotate_z(fdf->coord);
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
	{
		ft_rotate_y(fdf->coord);
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
	{
		ft_rotate_x(fdf->coord);
		ft_draw_grid(fdf, fdf->img);
	}
}
