/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_font.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:44:08 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/29 12:49:21 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_instructions(t_mc *fdf)
{
	mlx_put_string(fdf->mlx, "LEGEND", 100, 100);
	mlx_put_string(fdf->mlx, "Translation:", 50, 145);
	mlx_put_string(fdf->mlx, "Up:        8", 60, 165);
	mlx_put_string(fdf->mlx, "Down:      5", 60, 180);
	mlx_put_string(fdf->mlx, "Left:      4", 60, 195);
	mlx_put_string(fdf->mlx, "Right:     6", 60, 210);
	mlx_put_string(fdf->mlx, "Rotation:\n", 50, 235);
	mlx_put_string(fdf->mlx, "Reverse: Hold Space", 60, 255);
	mlx_put_string(fdf->mlx, "X-axis:    1", 60, 270);
	mlx_put_string(fdf->mlx, "Y-axis:    2", 60, 285);
	mlx_put_string(fdf->mlx, "Z-axis:    3", 60, 300);
	mlx_put_string(fdf->mlx, "Projection:\n", 50, 325);
	mlx_put_string(fdf->mlx, "Isometric: I", 60, 345);
	mlx_put_string(fdf->mlx, "XY-plane:  T", 60, 360);
	mlx_put_string(fdf->mlx, "XZ-plane:  S", 60, 375);
	mlx_put_string(fdf->mlx, "Color:     C", 50, 400);
	mlx_put_string(fdf->mlx, "Zoom:\n", 50, 425);
	mlx_put_string(fdf->mlx, "Maximize:  +", 60, 445);
	mlx_put_string(fdf->mlx, "Minimize:  -", 60, 460);
}
