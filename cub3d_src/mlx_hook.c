/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:55:59 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/16 18:34:20 by ibenmain         ###   ########.fr       */
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

void	ft_mlx_loop(t_data *data)
{
	mlx_hook(data->mlx.mlx_win, 02, 1L << 0, key_pressed, data);
	mlx_hook(data->mlx.mlx_win, 03, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx.mx, &ft_player_movement, data);
	mlx_loop(data->mlx.mx);
}
