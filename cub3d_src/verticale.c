/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verticale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:22:43 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/04 23:49:19 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int _is_wall(double next_hor_x, double next_hor_y, t_data *data)
{
	if (data->map[(int)(next_hor_x / TILE_SIZE)] \
		[(int)(next_hor_y / TILE_SIZE)] == '1')
		return (1);
	return (0);
}

void	ft_verticale(double xstep, double ystep, t_data *data)
{
	double x;

	x = 0;
	data->ray.next_ver_x = data->ray.xintercept_ver;
	data->ray.next_ver_y = data->ray.yintercept_ver;
	if (data->player.is_rayfacing_left)
		x = 1;
	// we just increment xstep and ystep until we find a wall
	while (data->ray.next_ver_x >= 0 && data->ray.next_ver_x \
		< data->line_max * TILE_SIZE && data->ray.next_ver_y >= 0 \
		&& data->ray.next_ver_y < data->len * TILE_SIZE)
	{
		if (_is_wall(data->ray.next_ver_y, data->ray.next_ver_x - x, data))
		{
			data->ray.found_wall_v = 1;
			data->ray.wall_hit_ver_x = data->ray.next_ver_x;
			data->ray.wall_hit_ver_y = data->ray.next_ver_y;
			break ;
		}
		data->ray.next_ver_x += xstep;
		data->ray.next_ver_y += ystep;
	}
}

void	ft_ray_cast_ver(t_data *data, double ray_angle)
{
	double	xstep;
	double	ystep;
	
	// find the x-coordinat of the closest verticale grid intersection
	data->ray.xintercept_ver = floor(data->player.pos_x \
	/ TILE_SIZE) * TILE_SIZE;
	// if the rayfacing right must add TILE_SIZE to yintercept if not don't do enything
	if (data->player.is_rayfacing_right)
		data->ray.xintercept_ver += TILE_SIZE;
	// find the y-coordinat of the closest verticale grid intersection
	data->ray.yintercept_ver = data->player.pos_y + \
	((data->ray.xintercept_ver - data->player.pos_x) * tan(ray_angle));
	// calculat the xstep and ystep (next step)
	xstep = TILE_SIZE;
	if (data->player.is_rayfacing_left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(ray_angle);
	if (data->player.is_rayfacing_up && ystep > 0)
		ystep *= -1;
	if (data->player.is_rayfacing_down && ystep < 0)
		ystep *= -1;
	ft_verticale(xstep, ystep, data);
}
