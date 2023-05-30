/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/30 13:30:13 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1024
# define HEIGHT 1024

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_point{
	int	x;
	int	y;
	int	z;
}	t_point;

void	ft_read_map(const char *pathname);

#endif