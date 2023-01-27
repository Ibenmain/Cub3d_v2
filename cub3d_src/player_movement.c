/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:04:15 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/27 19:51:26 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_has_wall(t_data *data, double x, double y)
{
	double	mapx;
	double	mapy;

	if (x < 0 || x > WIDTH_WIN || y < 0 || y > LENGHT_WIN)
		return (0);
	mapx = floor(x / TILE_SIZE);
	mapy = floor(y / TILE_SIZE);
	if ((data->map[(int)mapx][(int)floor(data->player.j / TILE_SIZE)] != '0' \
		&& data->map[(int)mapx][(int)floor(data->player.j / TILE_SIZE)] != 'N') \
		&& (data->map[(int)floor(data->player.i / TILE_SIZE)][(int)mapy] != '0' \
		&& data->map[(int)floor(data->player.i / TILE_SIZE)][(int)mapy] != 'N'))
		return (1);
	return (data->map[(int)mapx][(int)mapy] != '0' \
		&& data->map[(int)mapx][(int)mapy] != 'N');
}

void	ft_player_left(t_data *data)
{
	double	newposx;
	double	newposy;

	newposx = data->player.i + cos(data->player.rotationangl \
		+ (M_PI / 2)) * data->player.movespeed;
	newposy = data->player.j + sin(data->player.rotationangl \
		+ (M_PI / 2)) * data->player.movespeed;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.i = newposx;
		data->player.j = newposy;
	}
}

void	ft_player_right(t_data *data)
{
	double	newposx;
	double	newposy;

	newposx = data->player.i + cos(data->player.rotationangl \
		- (M_PI / 2)) * data->player.movespeed;
	newposy = data->player.j + sin(data->player.rotationangl \
		- (M_PI / 2)) * data->player.movespeed;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.i = newposx;
		data->player.j = newposy;
	}
}

void	ft_player_up(t_data *data)
{
	double	movestep;
	double	newposx;
	double	newposy;

	movestep = data->player.movespeed * data->player.walkdirection;
	newposx = data->player.i + cos(data->player.rotationangl) * movestep;
	newposy = data->player.j + sin(data->player.rotationangl) * movestep;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.i = newposx;
		data->player.j = newposy;
	}
}

void	ft_player_down(t_data *data)
{
	double	movestep;
	double	newposx;
	double	newposy;

	movestep = data->player.movespeed * data->player.walkdirection;
	newposx = data->player.i + cos(data->player.rotationangl) * movestep;
	newposy = data->player.j + sin(data->player.rotationangl) * movestep;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.i = newposx;
		data->player.j = newposy;
	}
}
