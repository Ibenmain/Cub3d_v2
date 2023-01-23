/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:59:01 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/23 01:08:10 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_circle(t_data *data, int x, int y, int color)
{
	double	i;
	double	j;
	double	angle;
	double	x1;
	double	y1;

	j = 0;
	while (j < 5)
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

void	draw_line(t_data *data, int x, int y, int color)
{
	double	j;
	double	x1;
	double	y1;

	j = 0;
	while (j < 20)
	{
		x1 = j * cos(data->player.rotationangl) * 5;
		y1 = j * sin(data->player.rotationangl) * 5;
		my_mlx_pixel_put(data, y + y1, x + x1, color);
		j += 0.1;
	}
}

double	ft_normalizeangle(double rayangle)
{
	rayangle = (int)rayangle % (int)(2 * M_PI);
	if (rayangle < 0)
		rayangle = (2 * M_PI) + rayangle;
	return (rayangle);
}

void	ft_raycast(t_data *data, double	rayangle)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	yintercept = floor(data->player.j / TILE_SIZE) * TILE_SIZE;
	yintercept += data->player.israyfacingd ? TILE_SIZE : 0;
	xintercept = data->player.i + (yintercept - data->player.j) / tan(rayangle);
	ystep = TILE_SIZE;
	ystep *= data->player.israyfacingu ? -1 : 1;
	xstep = TILE_SIZE / tan(rayangle);
	xstep *= (data->player.israyfacingl && xstep > 0) ? -1 : 1;
	xstep *= (data->player.israyfacingl && xstep < 0) ? -1 : 1;
}

void	draw_ray(t_data *data, int x, int y, int color)
{
	double	i;
	double	j;
	double	x1;
	double	y1;

	j = 0;
	i = 0;
	data->player.ray_angle = data->player.rotationangl \
		- (data->player.fov_angle / 2);
	while (i < data->player.num_ray)
	{
		data->player.ray_angle = ft_normalizeangle(data->player.ray_angle);
		ft_raycast(data, data->player.ray_angle);
		//raycast
		j = 0;
		while (j < 10)
		{
			x1 = j * cos(data->player.ray_angle) * 10;
			y1 = j * sin(data->player.ray_angle) * 10;
			my_mlx_pixel_put(data, y + y1, x + x1, color);
			j += 0.1;
		}
		data->player.ray_angle += data->player.fov_angle / data->player.num_ray;
		i++;
	}
}

void	ft_data_player(t_data *data)
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
				data->player.i = i * TILE_SIZE + TILE_SIZE / 2;
				data->player.j = j * TILE_SIZE + TILE_SIZE / 2;
				break ;
			}
			j++;
		}
		i++;
	}
}
