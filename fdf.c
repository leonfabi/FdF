/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:52:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/21 11:25:50 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void ft_error(void)
{
	printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}


void	ft_close_window(mlx_t *mlx, mlx_image_t *img)
{
		mlx_delete_image(mlx, img);
		mlx_close_window(mlx);
		//mlx_terminate(mlx);
}
void	ft_rotate_hook(void *param)
{
	t_mc	*fdf;
	t_list	*tmp;
	double	x_old;
	double	y_old;
	double	z_old;
	double	alpha;

	fdf = param;
	alpha = M_PI / 180 * 1;
	tmp = fdf->coord;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z)) //Z Axis rotation
	{
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
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y)) //Y Axis rotation
	{
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
		ft_draw_grid(fdf, fdf->img);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X)) //Y Axis rotation
	{
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
		ft_draw_grid(fdf, fdf->img);
	}
}
void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_mc *fdf;
	
	fdf = param;

	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		ft_printf("ESC pressed\n");
		ft_close_window(fdf->mlx, fdf->img);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf->y_rot = 0;
		fdf->x_rot = 0;
		fdf->z_rot = 0;
		fdf->x_trans = WIDTH / 2;
		fdf->y_trans = HEIGHT / 2;
		fdf->zoom = 1;
		ft_to_isometric(fdf);
	}
}

void	ft_move_hook(void *param)
{
	t_mc *fdf;

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
			((t_point *)tmp->c)->z_proj = fdf->zoom * ((t_point *)tmp->c)->z_proj;
			((t_point *)tmp->c)->y_proj = fdf->zoom * ((t_point *)tmp->c)->y_proj;
			((t_point *)tmp->c)->x_proj = fdf->zoom * ((t_point *)tmp->c)->x_proj;
			((t_point *)tmp->c)->x_draw = round(((t_point *)tmp->c)->x_proj);
			((t_point *)tmp->c)->y_draw = round(((t_point *)tmp->c)->y_proj);
			tmp = tmp->next;
		}
		ft_draw_grid(fdf, fdf->img);
	}
}

static void ft_hook(void* param)
{
	ft_move_hook(param);
	ft_rotate_hook(param);
	//ft_zoom_hook(param);
}

void	ft_draw_map(mlx_image_t *img, t_mc *fdf)
{
	t_list	*tmp;

	tmp = fdf->coord;
	while (tmp)
	{
		if (((t_point *) tmp->c)->x_draw >= 0 && ((t_point *) tmp->c)->y_draw >=0)
			mlx_put_pixel(img, (1) * ((t_point *) tmp->c)->x_draw,(1) * ((t_point *) tmp->c)->y_draw, 0xFF0000FF);
		tmp = tmp->next;
	}
}

void	ft_put_map(t_mc *fdf)
{
	t_list	*tmp;

	tmp = fdf->coord;
	ft_printf("Print Coordinates a:\n______\n");
	while (tmp)
	{
		ft_printf("(X:\t%d\t|Y:\t%d\t|Z:\t%d\t)\n", ((t_point *)tmp->c)->x, ((t_point *)tmp->c)->y, ((t_point *)tmp->c)->z);
		tmp = tmp->next;
	}
	ft_printf("END\n");
}

int	main(int argc, char **argv)
{
	t_mc	fdf;
	t_list	*tmp;

	fdf.coord = NULL;
	fdf.x_len = 0;
	fdf.x_trans = WIDTH / 2;
	fdf.y_trans = HEIGHT / 2;
	fdf.x_rot = 0;
	fdf.y_rot = 0;
	fdf.z_rot = 0;
	fdf.zoom = 1.0;
	if (argc != 2)
		return (EXIT_FAILURE);
	if (ft_read_map(&fdf, argv[1]) == -1)
		return (EXIT_FAILURE);
	ft_printf("Dimensions: x: %d, y: %d\n", fdf.x_len, fdf.y_len);
	tmp = fdf.coord;
	mlx_set_setting(MLX_DECORATED, true);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	if (!fdf.mlx)
		ft_error();
	// Create and display the image.
	fdf.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.img || (mlx_image_to_window(fdf.mlx, fdf.img, 0, 0) < 0))
		ft_error();
	ft_to_isometric(&fdf);
	ft_draw_grid(&fdf, fdf.img);
	mlx_key_hook(fdf.mlx, &my_keyhook, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_close_window(fdf.mlx);
	mlx_terminate(fdf.mlx);
	//ft_put_map(&fdf);
	ft_lstclear(&fdf.coord, &free);
	//system("leaks FdF");
	return (1);
}
