/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:34:58 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 21:02:03 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_draw_line(mlx_image_t *img, t_point p_0, t_point p_1, t_mc *fdf)
{
	int			dx;
	int			dy;
	int			err;
	int			sx;
	int			sy;
	int			e2;
	uint32_t	color;

	dx = abs(p_1.x_draw - p_0.x_draw);
	sx = p_0.x_draw < p_1.x_draw ? 1 : -1;
	dy = -abs(p_1.y_draw - p_0.y_draw);
	sy = p_0.y_draw < p_1.y_draw ? 1 : -1;
	err = dx + dy;
	color = get_rgba(0, 255, 0, 255);
	//color = (p_0.z - fdf->min) / (fdf->max - fdf->min) * (0xFFFFFFFF - 0xFF0000FF) + 0xFF0000FF;
	// if (p_0.z > fdf->min && p_0.z < (fdf->min + fdf->max) / 3)
	// 	color = 0xFF0000FF;
	// else if (p_0.z > (fdf->min + fdf->max) / 3 && p_0.z < (fdf->min + fdf->max) / 3 * 2)
	// 	color = 0x00FF00FF;
	// else
	// 	color = 0xFFFFFFFF;
	while (1)
	{
		if (p_0.x_draw + fdf->x_trans >= 0 && p_0.y_draw + fdf->y_trans >= 0 && p_0.x_draw + fdf->x_trans < WIDTH && p_0.y_draw + fdf->y_trans < HEIGHT)
			mlx_put_pixel(img, p_0.x_draw + fdf->x_trans, p_0.y_draw + fdf->y_trans, color);
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

void	ft_to_isometric(t_mc *fdf)
{
	double	x_pr;
	double	y_pr;
	double	z_pr;
	double	rad;
	int	y;
	int	x;

	rad = -M_PI / 4;
	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
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
			x++;
		}
		y++;
	}
	ft_draw_grid(fdf, fdf->img);
}

void	ft_to_oblique(t_mc *fdf)
{
	double	x_pr;
	double	y_pr;
	double	z_pr;
	double	rad;
	int	y;
	int	x;

	rad = M_PI / 4 * 2;
	y = 0;
	x = 0;
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			x_pr = SCALING * fdf->data[y][x].x;
			y_pr = SCALING * fdf->data[y][x].y;
			z_pr = SCALING * fdf->data[y][x].z;
			rad = -M_PI / 4;
			fdf->data[y][x].x_proj = x_pr;//round(- cos(rad) * z_pr * 0.5 + x_pr);
			fdf->data[y][x].y_proj = y_pr;//round(- sin(rad) * z_pr * 0.5 + y_pr);
			fdf->data[y][x].z_proj = z_pr;
			fdf->data[y][x].x_draw = fdf->data[y][x].x_proj;
			fdf->data[y][x].y_draw = fdf->data[y][x].y_proj;
			x++;
		}
		y++;
	}
	ft_draw_grid(fdf, fdf->img);
}
