/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:59:01 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/17 19:19:07 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == S)
		data->player.walkdirection = -1;
	else if (keycode == W)
		data->player.walkdirection = 1;
	else if (keycode == RIGHT_KEY)
		data->player.turndirection = 1;
	else if (keycode == LEFT_KEY)
		data->player.turndirection = -1;
	else if (keycode == A)
		data->player.sidedirection = -1;
	else if (keycode == D)
		data->player.sidedirection = 1;
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player.walkdirection = 0;
	else if (keycode == S)
		data->player.walkdirection = 0;
	else if (keycode == RIGHT_KEY)
		data->player.turndirection = 0;
	else if (keycode == LEFT_KEY)
		data->player.turndirection = 0;
	else if (keycode == A)
		data->player.sidedirection = 0;
	else if (keycode == D)
		data->player.sidedirection = 0;
	return (0);
}

void	draw_line(t_data *data, int x, int y, int color)
{
	double	j;
	double	x1;
	double	y1;

	j = 0;
	while (j < 10)
	{
		x1 = j * sin(data->player.rotationangl);
		y1 = j * cos(data->player.rotationangl);
		my_mlx_pixel_put(data, y + y1, x + x1, color);
		j += 0.1;
	}
}

double	ft_normalizeangle(double ray_angle)
{
	ray_angle = fmod(ray_angle, (2 * M_PI));
	if (ray_angle < 0)
		ray_angle += (2 * M_PI);
	return (ray_angle);
}

void	ft_position_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1' \
				&& data->map[i][j] != ' ')
			{
				data->player.pos_x = j * TILE_SIZE + TILE_SIZE / 2;
				data->player.pos_y = i * TILE_SIZE + TILE_SIZE / 2;
				break ;
			}
			j++;
		}
		i++;
	}
}
