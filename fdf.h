/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/30 08:45:45 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 256
# define HEIGHT 256

# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft/libft.h"

int	ft_read_map(const char *pathname);

#endif