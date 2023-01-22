/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:30:20 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/22 00:31:20 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_spase(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	get_line_map(t_data *data)
{
	int	line;
	int	i;

	i = 0;
	line = 0;
	data->line_max = 0;
	while (data->map[i])
	{
		if (data->line_max < ft_strlen(data->map[i]))
			data->line_max = ft_strlen(data->map[i]);
		if (ft_check_spase(data->map[i]))
			break ;
		line += 1;
		i++;
	}
	return (line);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < LENGHT_WIN && y >= 0 && y < WIDTH_WIN)
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
			if (i % TILE_SIZE == 0 || j % TILE_SIZE == 0)
				my_mlx_pixel_put(data, j, i, 0x00404040);
			else
				my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

int	ft_put_image_to_win(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->len)
	{
		j = -1;
		while (++j < data->line_max)
		{
			if (data->map[i][j] != ' ')
			{
				if (data->map[i][j] == '1')
					draw_rectangle(i, j, data, 0x000066CC);
				else
					draw_rectangle(i, j, data, 0x00CCCCFF);
			}
		}
	}
	draw_circle(data, data->player.i, data->player.j, 0x00000000);
	draw_line(data, data->player.i, data->player.j, 0x00000000);
	draw_ray(data, data->player.i, data->player.j, 0x00990000);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, \
		data->img.img, 0, 0);
	return (0);
}
