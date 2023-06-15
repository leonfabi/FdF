/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:34:58 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/15 16:19:30 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_line(mlx_image_t *img, t_point point0, t_point point1)
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
		if (point1.x_draw >= 0 && point0.x_draw >= 0 && point1.y_draw >= 0 && point0.y_draw >= 0)
		{
			mlx_put_pixel(img, point0.x_draw, point0.y_draw, 0xFF0000FF);
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
	ft_printf("Dimensions: x: %d, y: %d\n", fdf->x_len, fdf->y_len);
	while (tmp->next)
	{
		//ft_printf("Koordinaten: x: %d, Endbedingung: %d\n", ((t_point *)tmp->c)->x, fdf->x_len - 1);
		if (((t_point *)tmp->c)->x/SCALING < fdf->x_len - 1)
			ft_draw_line(img, *(t_point *)tmp->c, *(t_point *)tmp->next->c);
		if (((t_point *)tmp->c)->y/SCALING < fdf->y_len - 1)
			ft_draw_line(img, *(t_point *)tmp->c, *ft_next_y(tmp, fdf->x_len));
		tmp = tmp->next;
	}
}

void	ft_parse_to_isometric(t_mc *fdf)
{
	t_list	*tmp;

	tmp = fdf->coord;
	while (tmp)
	{
		
		tmp = tmp->next;
	}
}
