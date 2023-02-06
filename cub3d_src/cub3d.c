/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:09:42 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/06 22:30:22 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player(t_data *data)
{
	data->player.rotationangl = 3 * M_PI_2;
	data->player.movespeed = 2;
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
	data->img1.img1 = mlx_new_image(data->mlx.mx, WIDTH_WIN, HEIGHT_WIN);
	data->img1.addr1 = mlx_get_data_addr(data->img1.img1, \
		&data->img1.bits_per_pixel1, &data->img1.line_length1, &data->img1.endian1);
	int i = 0;
	int j;
	while (i < HEIGHT_WIN)
	{
		j = 0;
		while (j < WIDTH_WIN)
		{
			my_mlx_pixel_put1(data, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, data->img1.img1, 0, 0);
	
	ft_mlx_loop(data);
	
	return (0);
}




void	ft_cub3d(t_data *data)
{
	ft_data_player(data);
	ft_mlx_wind(data);
}
