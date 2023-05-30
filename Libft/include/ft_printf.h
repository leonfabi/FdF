/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:36:50 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/25 11:18:39 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *string, ...);

int		ft_xtoa_l_print(size_t integer, int *print);

int		ft_xtoa_u_print(size_t integer, int *print);

int		ft_putchar_print(char c, int *print);

int		ft_putstr_print(char *s, int *print);

size_t	ft_strlen(const char *s);

int		ft_putnbr_print(long n, int *print);

int		ft_putptr_print(void *ptr, int *print);

#endif
