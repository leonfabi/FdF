/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/29 14:18:14 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 2400
# define HEIGHT 1350
# define SCALING 20

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

typedef struct s_point{
	double	x;
	double	y;
	double	z;
	double	x_proj;
	double	y_proj;
	double	z_proj;
	double	x_draw;
	double	y_draw;
}	t_point;

typedef struct s_line_draw{
	int	dx;
	int	dy;
	int	err;
	int	sx;
	int	sy;
	int	e;
}	t_ld;

typedef struct s_map_coordinates{
	t_list		*input;
	t_point		**data;
	int			x_len;
	int			y_len;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_ld		draw;
	double		x_trans;
	double		y_trans;
	double		zoom;
	double		max;
	double		min;
	int			color;
}	t_mc;

int			ft_read_map(t_mc *fdf, const char *pathname);
void		ft_fill_data(t_mc *fdf);
void		ft_init(t_mc *fdf);
int			ft_init_data(t_mc *fdf);
void		ft_reset(t_mc *fdf, int mode);
void		ft_free_2d(char **tmp);
void		ft_free_data(t_point **tmp, int y_size);
void		ft_draw_line(mlx_image_t *img, t_point point0, \
			t_point point1, t_mc *fdf);
void		ft_draw_grid(t_mc *fdf, mlx_image_t *img);
void		ft_to_isometric(t_mc *fdf);
void		ft_to_xy(t_mc *fdf);
void		ft_to_yz(t_mc *fdf);
void		ft_rotate_hook(void *param);
void		ft_move_hook(void *param);
void		ft_zoom_hook(void *param);
void		ft_error(void);
uint32_t	get_rgba(int r, int g, int b, int a);
uint32_t	ft_color(int z, t_mc *fdf);
void		ft_instructions(t_mc *fdf);
int			ft_close_window(t_mc *fdf, int input, int data, int mlx);
#endif