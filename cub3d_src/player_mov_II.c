/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov_II.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:07:00 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/16 18:41:37 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

void	ft_wall_projection(t_data *data, int i)
{
	data->perp_disc = data->rays[i].distance * cos(data->rays[i].ray_angle \
		- data->player.rotationangl);
	data->disc_proj_plane = (WIDTH_WIN / 2) / tan(data->player. \
		fov_angle / 2.0);
	if (data->perp_disc == 0)
		data->perp_disc = 1;
	data->proj_wall_height = (TILE_SIZE / data->perp_disc) * \
		data->disc_proj_plane;
	data->rays[i].wall_strip_height = (int)data->proj_wall_height;
	data->rays[i].wall_top_pixl = (HEIGHT_WIN / 2.0) - \
		(data->rays[i].wall_strip_height / 2);
	if (data->rays[i].wall_top_pixl < 0)
		data->rays[i].wall_top_pixl = 0;
	data->rays[i].wall_bottom_pixl = (HEIGHT_WIN / 2) + \
		(data->rays[i].wall_strip_height / 2);
	if (data->rays[i].wall_bottom_pixl > HEIGHT_WIN)
		data->rays[i].wall_bottom_pixl = HEIGHT_WIN;
}

void	generate_projection(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->player.num_ray)
	{
		ft_wall_projection(data, i);
		j = 0;
		//set the color of the ceiling
		while (j++ < data->rays[i].wall_top_pixl)
			my_mlx_pixel_put1(data, i, j, create_trgb(0, data->val1_c, \
			data->val2_c, data->val3_c));
		//generate texture
		ft_rander_wall_strip(data, i);
		// set the color of the floor
		j = data->rays[i].wall_bottom_pixl;
		while (j++ < HEIGHT_WIN)
			my_mlx_pixel_put1(data, i, j, create_trgb(0, data->val1_f, \
			data->val2_f, data->val3_f));
		i++;
	}
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
		line += 1;
		i++;
	}
	return (line);
}

void	draw_rect(t_data *data)
{
	int	i;
	int	j;

	i = 0 ;
	while (i < data->len * TILE_SIZE)
	{
		j = 0;
		while (j < (data->line_max - 1) * TILE_SIZE)
		{
			if (i == 0 || i + 1 == (data->len) * TILE_SIZE)
				my_mlx_pixel_put(data, j, i, 0x000000);
			if (j == 0 || j + 1 == (data->line_max - 1) * TILE_SIZE)
				my_mlx_pixel_put(data, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int	ft_player_movement(t_data *data)
{
	if (data->player.walkdirection == 1)
		ft_player_up(data);
	if (data->player.walkdirection == -1)
		ft_player_down(data);
	if (data->player.sidedirection == -1)
		ft_player_left(data);
	if (data->player.sidedirection == 1)
		ft_player_right(data);
	if (data->player.turndirection == -1)
		data->player.rotationangl += data->player.rotationspeed \
			* data->player.turndirection;
	if (data->player.turndirection == 1)
		data->player.rotationangl += data->player.rotationspeed \
			* data->player.turndirection;
	data->player.rotationangl = fmod(data->player.rotationangl, (2 * M_PI));
	if (data->player.rotationangl < 0)
		data->player.rotationangl += (2 * M_PI);
	ft_put_image_to_win(data);
	return (0);
}
