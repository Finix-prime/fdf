/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:05:48 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/04 22:35:48 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "mlx/mlx.h"
#include "get_next_line/get_next_line.h"
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct	s_data {
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		dx;
	int		dy;
	int		dz;
	int		origin[2];
	int		metric[500][500];
	int		res[2];
}				t_data;

char	**split(char const *s, char c);
int		ft_atoi(const char *str);
int		wd_count(char const *s, char c);

#endif
