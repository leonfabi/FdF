/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:34:58 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 09:09:57 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_line(mlx_image_t *img, t_point p_0, t_point p_1, t_mc *fdf)
{
	int	dx;
	int	dy;
	int	err;
	int	sx;
	int	sy;
	int	e2;

	dx = abs(p_1.x_draw - p_0.x_draw);
	sx = p_0.x_draw < p_1.x_draw ? 1 : -1;
	dy = -abs(p_1.y_draw - p_0.y_draw);
	sy = p_0.y_draw < p_1.y_draw ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (p_0.x_draw + fdf->x_trans >= 0 && p_0.y_draw + fdf->y_trans >= 0 && p_0.x_draw + fdf->x_trans < WIDTH && p_0.y_draw + fdf->y_trans < HEIGHT)
			mlx_put_pixel(img, p_0.x_draw + fdf->x_trans, p_0.y_draw + fdf->y_trans, 0xFF0000FF);
		if (p_0.x_draw == p_1.x_draw && p_0.y_draw == p_1.y_draw) break;
		e2 = 2 * err;
		if (e2 > dy) { err += dy; p_0.x_draw += sx; } /* e_xy+e_x > 0 */
		if (e2 < dx) { err += dx; p_0.y_draw += sy; } /* e_xy+e_y < 0 */
	}
}

t_point	*ft_next_y(t_list *content, int x_len)
{
	while (x_len--)
		content = content->next;
	return (content->c);
}

void	ft_draw_grid(t_mc *fdf, mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	ft_bzero(img->pixels, WIDTH * HEIGHT * 4);
	while (y < fdf->y_len - 1)
	{
		x = 0;
		while (x < fdf->x_len - 1)
		{
			ft_draw_line(img, fdf->data[y][x], fdf->data[y][x + 1], fdf);
			ft_draw_line(img, fdf->data[y][x], fdf->data[y + 1][x], fdf);
			x++;
		}
		ft_draw_line(img, fdf->data[y][x], fdf->data[y + 1][x], fdf);
		y++;
	}
	x = 0;
	while (x < fdf->x_len - 1)
	{
		ft_draw_line(img, fdf->data[y][x], fdf->data[y][x + 1], fdf);
		x++;
	}
}

// void	ft_draw_grid(t_mc *fdf, mlx_image_t *img)
// {
// 	t_list	*tmp;
// 	int		count;

// 	tmp = fdf->coord;
// 	ft_bzero(img->pixels, WIDTH * HEIGHT * 4);
// 	while (tmp->next)
// 	{
// 		if (((t_point *)tmp->c)->x < fdf->x_len - 1)
// 			ft_draw_line(img, \
// 			*(t_point *)tmp->c, *(t_point *)tmp->next->c, fdf);
// 		if (((t_point *)tmp->c)->y < fdf->y_len - 1)
// 			ft_draw_line(img, \
// 			*(t_point *)tmp->c, *ft_next_y(tmp, fdf->x_len), fdf);
// 		tmp = tmp->next;
// 	}
// }

void	ft_to_isometric(t_mc *fdf)
{
	t_list	*tmp;
	double	x_pr;
	double	y_pr;
	double	z_pr;
	double	rad;

	tmp = fdf->coord;
	rad = -M_PI / 4;
	while (tmp)
	{
		x_pr = SCALING * ((t_point *)tmp->c)->x;
		y_pr = SCALING * ((t_point *)tmp->c)->y;
		z_pr = SCALING / 2 * ((t_point *)tmp->c)->z;
		rad = -M_PI / 4;
		((t_point *)tmp->c)->x_proj = round(cos(rad) * x_pr + sin(rad) * y_pr);
		y_pr = round(cos(rad) * y_pr - sin(rad) * x_pr);
		rad = M_PI / 180 * -30;
		((t_point *)tmp->c)->y_proj = round(cos(rad) * y_pr + sin(rad) * z_pr);
		((t_point *)tmp->c)->z_proj = round(cos(rad) * z_pr - sin(rad) * y_pr);
		((t_point *)tmp->c)->x_draw = ((t_point *)tmp->c)->x_proj;
		((t_point *)tmp->c)->y_draw = ((t_point *)tmp->c)->y_proj;
		tmp = tmp->next;
	}
	ft_draw_grid(fdf, fdf->img);
}
