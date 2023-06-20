/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:34:58 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/20 15:44:59 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_line(mlx_image_t *img, t_point point0, t_point point1, t_mc *fdf)
{
	int	dx;
	int	dy;
	int	err;
	int	sx;
	int	sy;
	int	e2;
	
	dx =  abs(point1.x_draw - point0.x_draw);
	sx = point0.x_draw < point1.x_draw ? 1 : -1;
	dy = -abs(point1.y_draw - point0.y_draw);
	sy = point0.y_draw < point1.y_draw ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (point1.x_draw + fdf->x_trans >= 0 && point0.x_draw + fdf->x_trans >= 0 && point1.y_draw + fdf->y_trans >= 0 && point0.y_draw + fdf->y_trans >= 0)
		{
			mlx_put_pixel(img, point0.x_draw + fdf->x_trans, point0.y_draw+ fdf->y_trans, 0xFF0000FF);
		}
		if (point0.x_draw == point1.x_draw && point0.y_draw == point1.y_draw) break;
		e2 = 2 * err;
		if (e2 > dy) { err += dy; point0.x_draw += sx; } /* e_xy+e_x > 0 */
		if (e2 < dx) { err += dx; point0.y_draw += sy; } /* e_xy+e_y < 0 */
	}

}
t_point	*ft_next_y(t_list	*content, int	x_len)
{
	while (x_len--)
		content = content->next;
	return (content->c);
}

void	ft_draw_grid(t_mc *fdf, mlx_image_t *img)
{
	t_list	*tmp;
	t_list	*tmp_row;
	int		count;

	tmp = fdf->coord;
	tmp_row = tmp;
	//ft_printf("Dimensions: x: %d, y: %d\n", fdf->x_len, fdf->y_len);
	ft_bzero(img->pixels, WIDTH * HEIGHT * 4);
	while (tmp->next)
	{
		//ft_printf("Koordinaten: x: %d, Endbedingung: %d\n", ((t_point *)tmp->c)->x, fdf->x_len - 1);
		if (((t_point *)tmp->c)->x < fdf->x_len - 1)
			ft_draw_line(img, *(t_point *)tmp->c, *(t_point *)tmp->next->c, fdf);
		if (((t_point *)tmp->c)->y < fdf->y_len - 1)
			ft_draw_line(img, *(t_point *)tmp->c, *ft_next_y(tmp, fdf->x_len), fdf);
		tmp = tmp->next;
	}
}

void	ft_to_isometric(t_mc *fdf)
{
	t_list	*tmp;
	double	x_old;
	double	y_old;
	double	z_old;

	tmp = fdf->coord;
	while (tmp)
	{
		x_old = ((t_point *)tmp->c)->x;
		y_old = ((t_point *)tmp->c)->y;
		y_old = ((t_point *)tmp->c)->z;
		((t_point *)tmp->c)->x = round(cos(M_PI / 4) * x_old + sin(M_PI / 4) * y_old);
		((t_point *)tmp->c)->y = round(cos(M_PI / 4) * y_old - sin(M_PI / 4) * x_old);
		//((t_point *)tmp->c)->x_draw = SCALING * ((t_point *)tmp->c)->x;
		//((t_point *)tmp->c)->y_draw = SCALING * ((t_point *)tmp->c)->y;
		tmp = tmp->next;
	}
	//ft_draw_grid(fdf, fdf->img);
}