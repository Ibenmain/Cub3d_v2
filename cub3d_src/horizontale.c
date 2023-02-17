/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:22:28 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/17 16:17:45 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

void	ft_horizontal(double xstep, double ystep, t_data *data)
{
	double	y;

	y = 0;
	data->ray.next_hor_x = data->ray.xintercept_hor;
	data->ray.next_hor_y = data->ray.yintercept_hor;
	if (data->player.is_rayfacing_up)
		y = 1;
	// we just increment xstep and ystep until we find a wall
	while (data->ray.next_hor_x >= 0 && data->ray.next_hor_x < \
		data->line_max * TILE_SIZE && data->ray.next_hor_y >= 0 \
		&& data->ray.next_hor_y < data->len * TILE_SIZE)
	{
		if (_is_wall(data->ray.next_hor_y - y, data->ray.next_hor_x, data))
		{
			data->ray.found_wall_h = 1;
			data->ray.wall_hit_hor_x = data->ray.next_hor_x;
			data->ray.wall_hit_hor_y = data->ray.next_hor_y;
			break ;
		}
		data->ray.next_hor_x += xstep;
		data->ray.next_hor_y += ystep;
	}
}

void	ft_ray_cast_hor(t_data *data, double ray_angle)
{
	double	xstep;
	double	ystep;
	// find the y-coordinat of the closest horizontal grid intersection
	data->ray.yintercept_hor = floor(data->player.pos_y / TILE_SIZE) \
		* TILE_SIZE;
	// if the rayfacing down must add TILE_SIZE to yintercept if not don't do enything
	if (data->player.is_rayfacing_down)
		data->ray.yintercept_hor += TILE_SIZE;
	// find the x-coordinat of the closest horizontal grid intersection
	data->ray.xintercept_hor = data->player.pos_x + \
	((data->ray.yintercept_hor - data->player.pos_y) / tan(ray_angle));
	// calculat the xstep and ystep (next step)
	ystep = TILE_SIZE;
	// increment or deincremenrt ystep of player 
	if (data->player.is_rayfacing_up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(ray_angle);
	if (data->player.is_rayfacing_left && xstep > 0)
		xstep *= -1;
	if (data->player.is_rayfacing_right && xstep < 0)
		xstep *= -1;
	ft_horizontal(xstep, ystep, data);
}
