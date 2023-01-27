 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:59:01 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/27 16:41:56 by ibenmain         ###   ########.fr       */
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

// int	__ft_has_wall_(t_data *data, double x, double y)
// {
// 	double	mapx;
// 	double	mapy;

// 	if (x < 0 || x > WIDTH_WIN || y < 0 || y > LENGHT_WIN)
// 		return (0);
// 	mapx = floor(x / TILE_SIZE);
// 	mapy = floor(y / TILE_SIZE);
// 	if ((data->map[(int)mapx][(int)floor(data->player.j / TILE_SIZE)] != '0' \
// 		&& data->map[(int)mapx][(int)floor(data->player.j / TILE_SIZE)] != 'N') \
// 		&& (data->map[(int)floor(data->player.i / TILE_SIZE)][(int)mapy] != '0' \
// 		&& data->map[(int)floor(data->player.i / TILE_SIZE)][(int)mapy] != 'N'))
// 		return (1);
// 	return (data->map[(int)mapx][(int)mapy] != '0' \
// 		&& data->map[(int)mapx][(int)mapy] != 'N');
// }

int	__ft_has_wall(t_data *data, double x, double y)
{
	double	mapx;
	double	mapy;

	if (x < 0 || x > WIDTH_WIN || y < 0 || y > LENGHT_WIN)
		return (0);
	mapx = floor(x / TILE_SIZE);
	mapy = floor(y / TILE_SIZE);

	return (data->map[(int)mapx][(int)mapy] != '0');
}

void	ft_horizontal_ray(t_data *data)
{
	double	nexthorztouchx = data->ray.xintercept;
	double	nexthorztouchy = data->ray.yintercept;
	double	foundhorzhit = 0;

	if (data->player.israyfacingu)
		nexthorztouchy--;
	// we just increment xstep and ystep until we find a wall
	while (nexthorztouchx > 0 && nexthorztouchx < WIDTH_WIN && nexthorztouchy > 0 && nexthorztouchy < LENGHT_WIN)
	{
		if (__ft_has_wall(data, nexthorztouchx, nexthorztouchy))
		{
			foundhorzhit = 1;
			data->ray.h_wallhitx = nexthorztouchx;
			data->ray.h_wallhity = nexthorztouchy;
			break ;
		}
		else
		{
			nexthorztouchx += data->ray.xstep;
			nexthorztouchy += data->ray.ystep;
		}
	}
	// draw_line(data, data->player.i, data->player.j, 0x00ffffff);
}

void	ft_raycast(t_data *data, double	rayangle)
{
	rayangle = data->player.rotationangl - (data->player.fov_angle / 2.0);
	// find the y-coordinat of the closest horizontal grid intersection
	data->ray.yintercept = floor(data->player.j / TILE_SIZE) * TILE_SIZE;
	// if the rayfacing down must add TILE_SIZE to yintercept if not don't do enything
	data->ray.yintercept += data->player.israyfacingd ? TILE_SIZE : 0;
	// find the x-coordinat of the closest horizontal grid intersection
	data->ray.xintercept = data->player.i + (data->ray.yintercept - data->player.j) / tan(rayangle);
	// calculat the xstep and ystep (next step)
	data->ray.ystep = TILE_SIZE;
	// increment or deincremenrt ystep of player 
	data->ray.ystep *= data->player.israyfacingu ? -1 : 1;
	data->ray.xstep = TILE_SIZE / tan(rayangle);
	data->ray.xstep *= (data->player.israyfacingl && data->ray.xstep > 0) ? -1 : 1;
	data->ray.xstep *= (data->player.israyfacingl && data->ray.xstep < 0) ? -1 : 1;
	ft_horizontal_ray(data);
}

// void	draw_ray(t_data *data, int x, int y, int color)
// {
// 	double	i;
// 	double	j;
// 	double	x1;
// 	double	y1;

// 	j = 0;
// 	i = 0;
// 	data->player.ray_angle = data->player.rotationangl \
// 		- (data->player.fov_angle / 2);
// 	// data->player.ray_angle = ft_normalizeangle(data->player.ray_angle);
// 	// ft_raycast(data, data->player.ray_angle);
// 	while (i < data->player.num_ray)
// 	{
// 		j = 0;
// 		while (j < 10)
// 		{
// 			x1 = j * cos(data->player.ray_angle) * data->player.h_wallhitx;
// 			y1 = j * sin(data->player.ray_angle) * data->player.h_wallhity;
// 			my_mlx_pixel_put(data, y + y1, x + x1, color);
// 			j += 0.1;
// 		}
// 		data->player.ray_angle += data->player.fov_angle / data->player.num_ray;
// 		i++;
// 	}
// }

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
	ft_raycast(data, 0);
}
