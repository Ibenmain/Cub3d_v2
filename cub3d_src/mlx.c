/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:30:20 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/16 18:33:55 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

int	ft_get_textur_affsetx(t_data *data, int i)
{
	int	textur_offset_x;
	int	direction;

	direction = ft_get_direction(data, i);
	if (data->rays[i].ver_hor)
		textur_offset_x = (data->rays[i].pos_ray_y / TILE_SIZE - (int) \
		(data->rays[i].pos_ray_y) / TILE_SIZE) * data->img_dir[direction].width;
	else
		textur_offset_x = (data->rays[i].pos_ray_x / TILE_SIZE - (int) \
		(data->rays[i].pos_ray_x) / TILE_SIZE) * data->img_dir[direction].width;
	return (textur_offset_x);
}

int	ft_get_textur_affsety(t_data *data, int j, int i, double w_s_height)
{
	int	distance_from_top;
	int	textur_offset_y;
	int	direction;

	direction = ft_get_direction(data, i);
	distance_from_top = j + (w_s_height / 2) - (HEIGHT_WIN / 2);
	textur_offset_y = (distance_from_top) * ((double)data->img_dir[direction]. \
		height / w_s_height);
	return (textur_offset_y);
}

int	ft_get_color(int i, t_data *data)
{
	int	clolor;
	int	direction;

	direction = ft_get_direction(data, i);
	clolor = *((int *)((data->img_dir[direction].addr) + ((int)(data->rays[i]. \
		textur_offset_y % data->img_dir[direction].height) * \
		data->img_dir[direction].line_length + (int)(data->rays[i]. \
		textur_offset_x % data->img_dir[direction].width) * \
		(data->img_dir[direction].bits_per_pixel / 8))));
	return (clolor);
}

void	ft_rander_wall_strip(t_data *data, int i)
{
	int	color;
	int	j;

	// rander the wall from the wallTopPixel to wallBottomPixel
	data->rays[i].textur_offset_x = ft_get_textur_affsetx(data, i);
	j = data->rays[i].wall_top_pixl;
	while (j++ < data->rays[i].wall_bottom_pixl)
	{
		data->rays[i].textur_offset_y = ft_get_textur_affsety(data, j, \
			i, data->rays[i].wall_strip_height);
		color = ft_get_color(i, data);
		my_mlx_pixel_put1(data, i, j, color);
	}
}

int	ft_put_image_to_win(t_data *data)
{
	mlx_clear_window(data->mlx.mx, data->mlx.mlx_win);
	ft_draw_map(data);
	draw_rect(data);
	ft_cast_rays(data);
	generate_projection(data);
	draw_circle(data, data->player.pos_y, data->player.pos_x, 0xFF0000);
	draw_line(data, data->player.pos_y, data->player.pos_x, 0xFF0000);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, \
		data->img_3d.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, \
		data->img_mini.img, 0, 0);
	return (0);
}
