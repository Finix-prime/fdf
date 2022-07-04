/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:50:22 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/04 16:28:10 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	circle(t_data data, int r)
{
	int	xs;
	int	ys;
	int	i;
	int	j;

	i = 1;
	j = 1;
	// (x + xs)**2 + (y + ys)**2 = r**2;
	while (i < 90)
	{
		xs = r * cos(i);
		ys = r * sin(i);
		if (i  > 90 && i <= 180)
		{
			xs = -xs;
		}
		if (i > 180 && i <= 270)
		{
			xs = -xs;
			ys = -ys;
		}
		if (i > 270)
			ys = -ys;
		my_mlx_pixel_put(&data, xs, ys, 0x00FF0000);
		printf("degree = %d xs = %d ys = %d\n", i, xs, ys);
		i++;
	}
}

void	retangle(int x, int y, int xs, int ys, t_data img)
{
	int i;

	i = y;
	while (x < xs)
	{
		while (y < ys)
		{
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
			my_mlx_pixel_put(&img, xs, y, 0x00FF0000);
			y++;
		}
		y = i;
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		my_mlx_pixel_put(&img, x, ys, 0x00FF0000);
		x++;
	}
}

void	hline(t_data img, int x, int y, int l)
{
	int	i;

	i = x;
	while (x < i + l)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
	}
}

void	vline(t_data img, int x, int y, int l)
{
	int	i;
	int xs;

	i = y;
	while (y < i + l)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		y++;
	}
}

void	grid(int x, int y, t_data img, t_mtx *mt)
{
	int	i;
	int	xs;
	int	ys;

	i = 0;
	xs = 0;
	ys = 0;
	while (i < mt->y)
	{
		hline(img, 0, 0 + ys, x * (mt->x - 1));
		ys += y;
		i++;
	}
	i = 0;
	while (i < mt->x)
	{
		vline(img, 0 + xs, 0, y * (mt->y - 1));
		xs += x;
		i++;
	}
	hline(img, 0, 0 + y, x);
	vline(img, 0 + x, 0, y);
}

void	inti_xyz(t_mtx *mt)
{
	mt->x = 0;
	mt->y = 0;
	mt->z = 0;
}

int	init_mt(t_mtx *mt, char *ln)
{
	char	**line;
	int		i;
	int		y;
	int		z;

	i = 0;
	y = mt->y;
	line = split(ln, ' ');
	z = ft_atoi(line[i]);
	while (i < wd_count(ln, ' ') && *line[i] != '\n')
	{
		mt->mt[i][y] = ft_atoi(line[i]);
		if (z < mt->mt[i][y])
			z = mt->mt[i][y];
		// printf("metric [%d][%d] = %d\n", i, y, mt->mt[i][y]);
		i++;
	}
	// printf("\n");
	return (i);
}

int draw_line(t_data *fdf, int beginY, int endX, int endY, int color)
{
	double	deltaX;
	double	deltaY;
	int 	pixels;
	double	pixelX;
	double	pixelY;

	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX = endX - beginX;
	deltaY = endY - beginY;
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(fdf->img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

int	main(void)
{
	void	*mlx;
	void	*win;
	int		res[2] = {1920, 1080};
	int		origin[2] = {200, 200};
	t_data	img;
	t_mtx	*mtr;

    char    *line;
	char	*buff;
    int     fd;

	mtr = (t_mtx *)malloc(sizeof(t_mtx));
	inti_xyz(mtr);
	// fd = open("my.fdf", O_RDONLY);
	fd = open("test_maps/10-2.fdf", O_RDONLY);
	// fd = open("test_maps/42.fdf", O_RDONLY);
	// fd = open("test_maps/elem-col.fdf", O_RDONLY);
	// fd = open("test_maps/elem2.fdf", O_RDONLY);
	// fd = open("test_maps/100-6.fdf", O_RDONLY);
	buff = "";
	while (read(fd, buff, BUFFER_SIZE))
	{
		line = get_next_line(fd);
		mtr->x = init_mt(mtr, line);
		mtr->y++;
	}
	printf("y = %d\n", mtr->y);
	printf("x = %d\n", mtr->x);
	free(line);
    close(fd);

	mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	// mlx_win = mlx_new_window(mlx, res[0], res[1], "Hello world!");
	// img.img = mlx_new_image(mlx, res[0], res[1]);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); // draw pixel
	// retangle(0, 0, 400, 400, img);
	// line(img, -190, 0, 500);
	// circle(img, 300);
	// grid(dim, 500, 500, img); // grid size 500(px) x 500(px)
	// grid(mtr->x, mtr->y, img, mtr);
	// draw_line(mlx, mlx_win, 640, 360, 0, 0, 0x00FF0000);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, origin[0], origin[1]);
	win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Draw Pixel");
	img.img = mlx_new_image(mlx, 640, 360);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	// mlx_pixel_put(mlx, win, 640/2, 360/2, 0xFF0000);
	draw_line(fdf, 640, 360, 0, 0, 0xFF0000);
	mlx_loop(mlx);
	free(mtr);
	return (0);
}
