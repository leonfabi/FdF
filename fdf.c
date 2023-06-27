/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:52:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 18:08:17 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

//void	ft_close_window(mlx_t *mlx, mlx_image_t *img)
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
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		ft_printf("ESC pressed\n");
		ft_close_window(fdf, 0);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf->x_trans = WIDTH / 2;
		fdf->y_trans = HEIGHT / 2;
		fdf->zoom = 1;
		ft_to_isometric(fdf);
	}
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_PRESS)
	{
		fdf->x_trans = WIDTH / 2;
		fdf->y_trans = HEIGHT / 2;
		fdf->zoom = 1;
		ft_to_oblique(fdf);
	}
}

static void	ft_hook(void *param)
{
	ft_move_hook(param);
	ft_rotate_hook(param);
	ft_zoom_hook(param);
}

int	main(int argc, char **argv)
{
	t_mc	fdf_new;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_init(&fdf_new);
	if (ft_read_map(&fdf_new, argv[1]) == -1)
		return (EXIT_FAILURE);
	ft_init_data(&fdf_new);
	mlx_set_setting(MLX_DECORATED, true);
	fdf_new.mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	if (!fdf_new.mlx)
		ft_error();
	fdf_new.img = mlx_new_image(fdf_new.mlx, WIDTH, HEIGHT);
	if (!fdf_new.img || (mlx_image_to_window(fdf_new.mlx, fdf_new.img, 0, 0) < 0))
	{
		ft_error();
		return (EXIT_FAILURE);
	}
	ft_fill_data(&fdf_new);
	ft_to_isometric(&fdf_new);
	mlx_key_hook(fdf_new.mlx, &my_keyhook, &fdf_new);
	mlx_loop_hook(fdf_new.mlx, ft_hook, &fdf_new);
	mlx_loop(fdf_new.mlx);
	ft_close_window(&fdf_new, 1);
	//system("leaks FdF");
	return (1);
}
