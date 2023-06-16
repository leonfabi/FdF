/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:52:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/16 13:19:57 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void ft_error(void)
{
	printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	ft_close_window(mlx_t *mlx, mlx_image_t *img)
{
		mlx_delete_image(mlx, img);
		mlx_close_window(mlx);
		//mlx_terminate(mlx);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_mc *fdf = param;

	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		ft_printf("ESC pressed\n");
		ft_close_window(fdf->mlx, fdf->img);
	}
}

void	ft_draw_coordinate_sys(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 512;
	x = 512;
	while(y++ < 1000)
		mlx_put_pixel(img, 512, y, 0x00FF00FF);
	while(x++ < 1000)
		mlx_put_pixel(img, x, 512, 0xFF0000FF);
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
	if (argc != 2)
		return (EXIT_FAILURE);
	ft_read_map(&fdf, argv[1]);//ft_strjoin("./maps/test_maps/", argv[1]));
	ft_printf("Dimensions: x: %d, y: %d\n", fdf.x_len, fdf.y_len);
	tmp = fdf.coord;
	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_DECORATED, true);
	// mlx_t* mlx
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	// if (!mlx)
	// 	ft_error();

	/* Do stuff */

	// Create and display the image.
	// mlx_image_t* img 
	fdf.img = mlx_new_image(fdf.mlx, HEIGHT, WIDTH);
	if (!fdf.img || (mlx_image_to_window(fdf.mlx, fdf.img, 0, 0) < 0))
		ft_error();
	//ft_draw_line(img, &fdf);
	//ft_draw_coordinate_sys(img);
	ft_draw_map(fdf.img, &fdf);
	ft_draw_grid(&fdf, fdf.img);
	// while (tmp->next)
	// {
	// 	ft_draw_line(img, *(t_point *)tmp->c, *(t_point *)tmp->next->c);
	// 	tmp = tmp->next;
	// }
	// Even after the image is being displayed, we can still modify the buffer.

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(fdf.mlx, &my_keyhook, &fdf);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(fdf.mlx);
	mlx_close_window(fdf.mlx);
	mlx_terminate(fdf.mlx);
	//ft_put_map(&fdf);
	ft_lstclear(&fdf.coord, &free);
	//system("leaks FdF");
	return (1);
}
