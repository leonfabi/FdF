/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:34:58 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 11:07:47 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_line_loop(mlx_image_t *img, t_point p_0, t_point p_1, t_mc *fdf)
{
	uint32_t	color;

	color = get_rgba(255, 255, 255, 255);
	if (fdf->color)
		color = ft_color(p_0, fdf);
	while (1)
	{
		if (p_0.x_draw + fdf->x_trans >= 0 && p_0.y_draw + fdf->y_trans >= 0 && \
		p_0.x_draw + fdf->x_trans < WIDTH && p_0.y_draw + fdf->y_trans < HEIGHT)
			mlx_put_pixel(img, p_0.x_draw + fdf->x_trans, \
			p_0.y_draw + fdf->y_trans, color);
		if (p_0.x_draw == p_1.x_draw && p_0.y_draw == p_1.y_draw)
			break ;
		fdf->draw.e = 2 * fdf->draw.err;
		if (fdf->draw.e > fdf->draw.dy)
		{
			fdf->draw.err += fdf->draw.dy;
			p_0.x_draw += fdf->draw.sx;
		}
		if (fdf->draw.e < fdf->draw.dx)
		{
			fdf->draw.err += fdf->draw.dx;
			p_0.y_draw += fdf->draw.sy;
		}
	}
}

void	ft_draw_line(mlx_image_t *img, t_point p_0, t_point p_1, t_mc *fdf)
{
	fdf->draw.dx = fabs(p_1.x_draw - p_0.x_draw);
	if (p_0.x_draw < p_1.x_draw)
	{
		fdf->draw.sx = 1;
	}
	else
	{
		fdf->draw.sx = -1;
	}
	fdf->draw.dy = -fabs(p_1.y_draw - p_0.y_draw);
	if (p_0.y_draw < p_1.y_draw)
	{
		fdf->draw.sy = 1;
	}
	else
	{
		fdf->draw.sy = -1;
	}
	fdf->draw.err = fdf->draw.dx + fdf->draw.dy;
	ft_draw_line_loop(img, p_0, p_1, fdf);
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
