/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:49:21 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/04 22:33:55 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calcule_dis(t_data *data)
{
	double	ver_dis;
	double	hor_dis;

	// we need get the smaller distanc between horizontal & vertical
	ver_dis = hypot(data->player.pos_x - data->ray.wall_hit_ver_x, \
	data->player.pos_y - data->ray.wall_hit_ver_y);
	hor_dis = hypot(data->player.pos_x - data->ray.wall_hit_hor_x, \
	data->player.pos_y - data->ray.wall_hit_hor_y);
	if (data->ray.found_wall_h && data->ray.found_wall_v)
	{
		if (ver_dis <= hor_dis)
			DDA(data->player.pos_x, data->player.pos_y, \
			data->ray.wall_hit_ver_x, data->ray.wall_hit_ver_y, data);
		else
			DDA(data->player.pos_x, data->player.pos_y, \
			data->ray.wall_hit_hor_x, data->ray.wall_hit_hor_y, data);
	}
	else if (data->ray.found_wall_h)
		DDA(data->player.pos_x, data->player.pos_y, \
		data->ray.wall_hit_hor_x, data->ray.wall_hit_hor_y, data);
	else if (data->ray.found_wall_v)
		DDA(data->player.pos_x, data->player.pos_y, \
		data->ray.wall_hit_ver_x, data->ray.wall_hit_ver_y, data);
	return (0);
}

void	ft_initial_var(t_data *data)
{
	data->ray.next_hor_x = 0;
	data->ray.next_hor_y = 0;
	data->ray.wall_hit_hor_x = 0;
	data->ray.wall_hit_hor_y = 0;
	data->ray.yintercept_hor = 0;
	data->ray.xintercept_hor = 0;
	data->ray.found_wall_h = 0;
	data->player.is_rayfacing_up = 0;
	data->player.is_rayfacing_down = 0;
	data->player.is_rayfacing_left = 0;
	data->player.is_rayfacing_right = 0;
	data->ray.next_ver_x = 0;
	data->ray.next_ver_y = 0;
	data->ray.wall_hit_ver_x = 0;
	data->ray.wall_hit_ver_y = 0;
	data->ray.yintercept_ver = 0;
	data->ray.xintercept_ver = 0;
	data->ray.found_wall_v = 0;
}

void	ft_determine_the_trends(double rayangle, t_data *data)
{
	if (rayangle > 0 && rayangle < M_PI)
		data->player.is_rayfacing_down = 1;
	data->player.is_rayfacing_up = !data->player.is_rayfacing_down;
	if (rayangle < M_PI_2 || rayangle > (3 * M_PI_2))
		data->player.is_rayfacing_right = 1;
	data->player.is_rayfacing_left = !data->player.is_rayfacing_right;
}

void	ft_cast_rays(t_data *data)
{
	double rayangle;
	int i = 0;

	rayangle = data->player.rotationangl - (data->player.fov_angle / 2);
	while (i < data->player.num_ray)
	{
		ft_initial_var(data);
		rayangle = ft_normalizeangle(rayangle);
		ft_determine_the_trends(rayangle, data);
		ft_ray_cast_hor(data, rayangle);
		ft_ray_cast_ver(data, rayangle);
		calcule_dis (data);
		rayangle += data->player.fov_angle / data->player.num_ray;
		i++;
	}
}