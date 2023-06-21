/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:52:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/21 14:07:47 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	ft_close_window(mlx_t *mlx, mlx_image_t *img)
{
		mlx_delete_image(mlx, img);
		mlx_close_window(mlx);
		//mlx_terminate(mlx);
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

static void ft_hook(void* param)
{
	ft_move_hook(param);
	ft_rotate_hook(param);
	//ft_zoom_hook(param);
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
	{
		ft_lstclear(&fdf.coord, &free);
		return (EXIT_FAILURE);
	}
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
	ft_lstclear(&fdf.coord, &free);
	//system("leaks FdF");
	return (1);
}
