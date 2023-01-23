/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:09:42 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/23 00:32:30 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player(t_data *data)
{
	double	ray_angl;

	ray_angl = data->player.rotationangl \
		- (data->player.fov_angle / 2);
	data->player.rotationangl = 0;
	data->player.movespeed = 3;
	data->player.walkdirection = 0;
	data->player.sidedirection = 0;
	data->player.turndirection = 0;
	data->player.rotationspeed = 3 * (M_PI / 180);
	data->player.fov_angle = 60 * (M_PI / 180);
	data->player.num_ray = WIDTH_WIN;
	data->player.wallhitx = 0;
	data->player.wallhity = 0;
	data->player.distanc = 0;
	data->player.israyfacingd = ray_angl > 0 && ray_angl < M_PI;
	data->player.israyfacingu = !data->player.israyfacingd;
	data->player.israyfacingr = ray_angl < 0.5 * M_PI || ray_angl > 1.5 * M_PI;
	data->player.israyfacingl = !data->player.israyfacingr;
	data->player.i = -1;
	data->player.j = -1;
}

int	ft_mlx_wind(t_data *data)
{
	data->len = get_line_map(data);
	data->mlx.mx = mlx_init();
	if (!data->mlx.mx)
		return (-1);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mx, \
		LENGHT_WIN, WIDTH_WIN, "./cub3d");
	if (!data->mlx.mlx_win)
		return (-1);
	data->img.img = mlx_new_image(data->mlx.mx, LENGHT_WIN, WIDTH_WIN);
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
