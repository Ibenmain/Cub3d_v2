/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:30:58 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/06 22:24:07 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put1(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= WIDTH_WIN && y >= 0 && y <= HEIGHT_WIN)
	{
		dst = data->img1.addr1 + (y * data->img1.line_length1 + x * \
			(data->img1.bits_per_pixel1 / 8));
		*(unsigned int *)dst = color;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= data->line_max * TILE_SIZE \
		&& y >= 0 && y <= data->len * TILE_SIZE)
	{
		dst = data->img.addr + (y * data->img.line_length + x * \
			(data->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_rectangle(int x, int y, t_data *data, int color)
{
	int	i;
	int	j;

	i = x * TILE_SIZE;
	while (i < x * TILE_SIZE + TILE_SIZE)
	{
		j = y * TILE_SIZE;
		while (j < y * TILE_SIZE + TILE_SIZE)
		{
			if ((i % TILE_SIZE == 0 || j % TILE_SIZE == 0) && data->map[(int)(i / TILE_SIZE)][(int)(j / TILE_SIZE)] != ' ')
				my_mlx_pixel_put(data, j, i, 0x00404040);
			else
				my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_data *data)
{
	int		i;
	int		j;
	
	i = -1;
	while (++i < data->len)
	{
		j = -1;
		while (++j < data->line_max)
		{
				if (data->map[i][j] == ' ')
					draw_rectangle(i, j, data, 0xFF000000);
				else if (data->map[i][j] == '1')
					draw_rectangle(i, j, data, 0x000066CC);
				else
					draw_rectangle(i, j, data, 0x00CCCCFF);
		}
		
	}
}

void	draw_circle(t_data *data, int x, int y, int color)
{
	double	i;
	double	j;
	double	angle;
	double	x1;
	double	y1;

	j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 360)
		{
			angle = i;
			x1 = j * cos(angle * M_PI / 180);
			y1 = j * sin(angle * M_PI / 180);
			my_mlx_pixel_put(data, y + y1, x + x1, color);
			i += 0.1;
		}
		j += 0.1;
	}
}
