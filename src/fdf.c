/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:52:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/28 14:54:25 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	ft_close_window(t_mc *fdf, int clean)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	mlx_close_window(fdf->mlx);
	if (clean)
	{
		ft_lstclear(&fdf->input, &free);
		ft_free_data(fdf->data, fdf->y_len - 1);
		mlx_terminate(fdf->mlx);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mc	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_close_window(fdf, 0);
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		ft_reset(fdf, 0);
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		ft_reset(fdf, 1);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		ft_reset(fdf, 2);
	if (keydata.key == MLX_KEY_G && keydata.action == MLX_PRESS)
		ft_reset(fdf, 3);
}

static void	ft_hook(void *param)
{
	ft_move_hook(param);
	ft_rotate_hook(param);
	ft_zoom_hook(param);
}

int	main(int argc, char **argv)
{
	t_mc	fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_init(&fdf);
	if (ft_read_map(&fdf, argv[1]) == -1)
		return (EXIT_FAILURE);
	ft_init_data(&fdf);
	mlx_set_setting(MLX_DECORATED, true);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	if (!fdf.mlx)
		ft_error();
	fdf.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.img || (mlx_image_to_window(fdf.mlx, fdf.img, 0, 0) < 0))
	{
		ft_error();
		return (EXIT_FAILURE);
	}
	ft_fill_data(&fdf);
	ft_to_isometric(&fdf);
	mlx_key_hook(fdf.mlx, &my_keyhook, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	ft_close_window(&fdf, 1);
	//system("leaks FdF");
	return (1);
}
