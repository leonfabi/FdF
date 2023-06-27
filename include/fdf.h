/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 18:07:37 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080
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
	double			x;
	double			y;
	double			z;
	double			x_proj;
	double			y_proj;
	double			z_proj;
	double			x_draw;
	double			y_draw;
}	t_point;

typedef struct s_map_coordinates{
	t_list		*input;
	t_point		**data;
	int			x_len;
	int			y_len;
	mlx_image_t	*img;
	mlx_t		*mlx;
	double		x_trans;
	double		y_trans;
	double		zoom;
}	t_mc;

int		ft_read_map(t_mc *fdf, const char *pathname);
int		ft_fill_data(t_mc *fdf);
int		ft_init(t_mc *fdf);
int		ft_init_data(t_mc *fdf);
void	ft_free_2d(char **tmp);
void	ft_free_data(t_point **tmp, int y_size);
void	ft_draw_line(mlx_image_t *img, t_point point0, \
		t_point point1, t_mc *fdf);
void	ft_draw_grid(t_mc *fdf, mlx_image_t *img);
void	ft_to_isometric(t_mc *fdf);
void	ft_to_oblique(t_mc *fdf);
void	ft_rotate_hook(void *param);
void	ft_move_hook(void *param);
void	ft_zoom_hook(void *param);
void	ft_error(void);
#endif