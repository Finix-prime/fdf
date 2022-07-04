/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:04:55 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/04 22:35:40 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_mt(t_data *fdf, char *ln)
{
	char	**line;
	int		i;
	int		y;

	i = 0;
	y = fdf->dy;
	line = split(ln, ' ');
	fdf->dz = ft_atoi(line[i]);
	while (i < wd_count(ln, ' ') && *line[i] != '\n')
	{
		fdf->metric[i][y] = ft_atoi(line[i]);
		if (fdf->metric[i][y] > fdf->dz)
			fdf->dz = fdf->metric[i][y];
		i++;
	}
	return (i);
}

void	read_maps(t_data *fdf, char *map)
{
	char    *line;
	char	*buff;
	int		fd;

	buff = "";
	fdf->dy = 0;
	fd = open(map, O_RDONLY);
	while (read(fd, buff, BUFFER_SIZE))
	{
		line = get_next_line(fd);
		fdf->dx = init_mt(fdf, line);
		fdf->dy++;
	}
    close(fd);
	free(line);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	hline(t_data *fdf, int l)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = fdf->origin[0];
	y = fdf->origin[1];
	while (i < l)
	{
		my_mlx_pixel_put(fdf, x + i, y, 0x00FF0000);
		i++;
	}
}

void	vline(t_data *fdf, int l)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = fdf->origin[0];
	y = fdf->origin[1];
	while (i < l)
	{
		my_mlx_pixel_put(fdf, x, y + i, 0x00FF0000);
		i++;
	}
}

int draw_line(t_data *fdf, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX;
	double deltaY;
	double pixelX;
	double pixelY;
	int pixels;


	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixelY = beginY;
	pixelX = beginX;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	// printf("pixel = %d delX =%.2f delY =%.2f pix X=%.2f pix Y=%.2f\n", pixels, deltaX, deltaY, pixelX, pixelY);
	color = 0x00FF0000;
	while (pixels)
	{
		my_mlx_pixel_put(fdf, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

int	main(void)
{
	t_data	*fdf;
	char	*line;
	int		color;

	color = 0x00FF0000;
	fdf = (t_data *)malloc(sizeof(t_data));
	read_maps(fdf, "test_maps/10-2.fdf");
	printf("dx = %d dy = %d dz = %d\n", fdf->dx, fdf->dy, fdf->dz);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "Hello Fdf");
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	printf("bits_per_pixel = %d line_length = %d endian = %d\n", fdf->bits_per_pixel, fdf->line_length, fdf->endian);
	my_mlx_pixel_put(fdf, 50, 50, color);
	my_mlx_pixel_put(fdf, 50, 100, color);
	// draw_line(fdf, 1920, 1080, 0, 0, color);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_loop(fdf->mlx);
	free(fdf);
	return (0);
}
