/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:55:59 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/18 14:42:12 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	dda(double X1, double Y1, t_data *data)
{
	double	x;
	double	y;
	int		i;

	i = 0;
	data->dx = X1 - data->player.pos_x;
	data->dy = Y1 - data->player.pos_y;
	data->steps = fmax(fabs(data->dx), fabs(data->dy));
	data->xincrement = data->dx / data->steps;
	data->yincrement = data->dy / data->steps;
	x = data->player.pos_x;
	y = data->player.pos_y;
	while (i <= data->steps)
	{
		my_mlx_pixel_put(data, round(x), round(y), 0xFFFFCC);
		x += data->xincrement;
		y += data->yincrement;
		i++;
	}
}

int	ft_get_direction(t_data *data, int i)
{
	int	dir;

	dir = -1;
	if (!data->rays[i].ver_hor && data->rays[i].dir_up)
		dir = NO;
	else if (data->rays[i].ver_hor && data->rays[i].dir_right)
		dir = EA;
	else if (!data->rays[i].ver_hor && data->rays[i].dir_down)
		dir = SO;
	else if (data->rays[i].ver_hor && data->rays[i].dir_left)
		dir = WE;
	return (dir);
}

int	ft_check_spase(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	_handler_mouse(int y, int x, t_data *data)
{
	mlx_clear_window(data->mlx.mx, data->mlx.mlx_win);
	if (y > 0 && y < WIDTH_WIN && x > 0 && x < HEIGHT_WIN)
	{
		if (data->mouse != y)
		{
			if (y > data->mouse)
				data->player.turndirection = 1;
			else
				data->player.turndirection = -1;
		}
	}
	data->mouse = y;
	ft_player_movement(data);
	data->player.turndirection = 0;
	return (0);
}

int	handl_keyrelease(t_data *data)
{
	ft_free_all_data(data);
	exit(0);
}

void	ft_mlx_loop(t_data *data)
{
	mlx_hook(data->mlx.mlx_win, 02, 1L, key_pressed, data);
	mlx_hook(data->mlx.mlx_win, 03, 1L, key_release, data);
	mlx_hook(data->mlx.mlx_win, 06, 1L, &_handler_mouse, data);
	mlx_hook(data->mlx.mlx_win, 17, 1L, &handl_keyrelease, data);
	mlx_loop_hook(data->mlx.mx, &ft_player_movement, data);
	mlx_loop(data->mlx.mx);
}
