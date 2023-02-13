/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:09:42 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/13 15:21:02 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

void	ft_get_direction_player(t_data *data)
{
	if (data->dir.n)
		data->player.rotationangl = 3 * M_PI_2;
	else if (data->dir.s)
		data->player.rotationangl = M_PI_2;
	else if (data->dir.e)
		data->player.rotationangl = 0;
	else if (data->dir.w)
		data->player.rotationangl = M_PI;
}

void	ft_init_player(t_data *data)
{
	ft_get_direction_player(data);
	data->player.movespeed = 2;
	data->player.walkdirection = 0;
	data->player.sidedirection = 0;
	data->player.turndirection = 0;
	data->player.rotationspeed = 0.1;
	data->player.fov_angle = 60 * (M_PI / 180);
	data->player.num_ray = WIDTH_WIN;
	data->player.pos_x = -1;
	data->player.pos_y = -1;
	data->player.wall_hit_x = 0;
	data->player.wall_hit_y = 0;
	data->wall_texture = (unsigned int *)malloc(sizeof(unsigned int) * (TEXTURE_WIDTH * TEXTURE_HEIGHT));
}

int	ft_mlx_wind(t_data *data)
{
	int	h;
	int	w;

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
	data->img1.img1 = mlx_new_image(data->mlx.mx, WIDTH_WIN, HEIGHT_WIN);
	data->img1.addr1 = mlx_get_data_addr(data->img1.img1, \
		&data->img1.bits_per_pixel1, &data->img1.line_length1, &data->img1.endian1);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, data->img1.img1, 0, 0);
	data->imgwall.imgwall = mlx_xpm_file_to_image(data->mlx.mx, "image/wallnumber1.xpm", &w, &h);
	data->imgwall.addrwall = mlx_get_data_addr(data->imgwall.imgwall, \
		&data->imgwall.bits_per_pixelwall, &data->imgwall.line_lengthwall, &data->imgwall.endianwall);
	return (0);
}

void	ft_cub3d(t_data *data)
{
	ft_position_player(data);
	data->rays = (t_rays *)malloc(sizeof(t_rays) * data->player.num_ray);
	if (!data->rays)
		ft_print_error("error: allocation failed", data);
	ft_mlx_wind(data);
	ft_mlx_loop(data);
}
