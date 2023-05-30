/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:52:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/30 13:33:54 by fkrug            ###   ########.fr       */
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

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	const mlx_t* mlx = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		
	}

}
void	ft_close_window(mlx_t *mlx, mlx_image_t *img)
{
		mlx_delete_image(mlx, img);
		mlx_close_window(mlx);
		mlx_terminate(mlx);
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

int	main(void)
{

ft_read_map("./maps/test_maps/10-2.fdf");

	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_DECORATED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 1024, 1024);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	ft_draw_coordinate_sys(img);
	// Even after the image is being displayed, we can still modify the buffer.

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, &my_keyhook, NULL);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
