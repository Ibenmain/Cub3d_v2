/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:09:42 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/06 22:28:51 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player(t_data *data)
{
	data->player.rotationangl = M_PI_2;
	data->player.movespeed = 1.5;
	data->player.walkdirection = 0;
	data->player.sidedirection = 0;
	data->player.turndirection = 0;
	data->player.rotationspeed = 0.03;
	data->player.fov_angle = 60 * (M_PI / 180);
	data->player.num_ray = WIDTH_WIN;
	data->player.pos_x = -1;
	data->player.pos_y = -1;
	data->player.wall_hit_x = 0;
	data->player.wall_hit_y = 0;
	//allocate the total amount of bytes in memory to hold our color buffer
	// data->colorbuffer = malloc(sizeof(char) * WIDTH_WIN * HEIGHT_WIN);
}

int	ft_mlx_wind(t_data *data)
{
	data->len = get_line_map(data);
	data->mlx.mx = mlx_init();
	if (!data->mlx.mx)
		return (-1);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mx, \
		WIDTH_WIN, HEIGHT_WIN, "./cub3d");
	if (!data->mlx.mlx_win)
		return (-1);
	data->img.img = mlx_new_image(data->mlx.mx, data->line_max \
		* TILE_SIZE, data->len * TILE_SIZE);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	ft_mlx_loop(data);
	
	return (0);
}




void	ft_cub3d(t_data *data)
{
	ft_data_player(data);
	ft_mlx_wind(data);
}
