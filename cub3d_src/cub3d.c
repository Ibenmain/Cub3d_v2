/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:09:42 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/17 15:44:42 by ibenmain         ###   ########.fr       */
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
	data->mouse = WIDTH_WIN / 2;
}

void	ft_get_addr_of_image(t_data *data)
{
	data->img_dir[NO].img = mlx_xpm_file_to_image(data->mlx.mx, data->map1 \
		.no_path, &data->img_dir[NO].width, &data->img_dir[NO].height);
	if (!data->img_dir[NO].img)
		ft_print_error("error: empty file\n");
	data->img_dir[NO].addr = mlx_get_data_addr(data->img_dir[NO].img, \
		&data->img_dir[NO].bits_per_pixel, &data->img_dir[NO].line_length, \
		&data->img_dir[NO].endian);
	data->img_dir[SO].img = mlx_xpm_file_to_image(data->mlx.mx, data->map1. \
		so_path, &data->img_dir[SO].width, &data->img_dir[SO].height);
	if (!data->img_dir[SO].img)
		ft_print_error("error: empty file\n");
	data->img_dir[SO].addr = mlx_get_data_addr(data->img_dir[SO].img, \
		&data->img_dir[SO].bits_per_pixel, &data->img_dir[SO].line_length, \
		&data->img_dir[SO].endian);
	data->img_dir[WE].img = mlx_xpm_file_to_image(data->mlx.mx, data->map1. \
		we_path, &data->img_dir[WE].width, &data->img_dir[WE].height);
	if (!data->img_dir[WE].img)
		ft_print_error("error: empty file\n");
	data->img_dir[WE].addr = mlx_get_data_addr(data->img_dir[WE].img, \
		&data->img_dir[WE].bits_per_pixel, &data->img_dir[WE].line_length, \
		&data->img_dir[WE].endian);
	data->img_dir[EA].img = mlx_xpm_file_to_image(data->mlx.mx, data->map1. \
		ea_path, &data->img_dir[EA].width, &data->img_dir[EA].height);
	if (!data->img_dir[EA].img)
		ft_print_error("error: empty file\n");
	data->img_dir[EA].addr = mlx_get_data_addr(data->img_dir[EA].img, \
		&data->img_dir[EA].bits_per_pixel, &data->img_dir[EA].line_length, \
		&data->img_dir[EA].endian);
}

int	ft_mlx_wind(t_data *data)
{
	data->len = get_line_map(data);
	data->mlx.mx = mlx_init();
	if (!data->mlx.mx)
		return (-1);
	if (WIDTH_WIN >= 5120 || HEIGHT_WIN >= 2880)
		ft_print_error("error: the size too biggest\n");
	data->mlx.mlx_win = mlx_new_window(data->mlx.mx, \
		WIDTH_WIN, HEIGHT_WIN, "./cub3d");
	if (!data->mlx.mlx_win)
		return (-1);
	data->img_mini.img = mlx_new_image(data->mlx.mx, data->line_max \
		* TILE_SIZE, data->len * TILE_SIZE);
	data->img_mini.addr = mlx_get_data_addr(data->img_mini.img, \
		&data->img_mini.bits_per_pixel, &data->img_mini.line_length, \
		&data->img_mini.endian);
	data->img_3d.img = mlx_new_image(data->mlx.mx, WIDTH_WIN, HEIGHT_WIN);
	data->img_3d.addr = mlx_get_data_addr(data->img_3d.img, &data->img_3d. \
		bits_per_pixel, &data->img_3d.line_length, &data->img_3d.endian);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, \
		data->img_3d.img, 0, 0);
	ft_get_addr_of_image(data);
	return (0);
}

void	ft_cub3d(t_data *data)
{
	ft_position_player(data);
	data->rays = (t_rays *)malloc(sizeof(t_rays) * data->player.num_ray);
	if (!data->rays)
		ft_print_error("error: allocation failed");
	ft_mlx_wind(data);
	ft_mlx_loop(data);
}
