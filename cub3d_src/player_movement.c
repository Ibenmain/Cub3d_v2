/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:04:15 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/30 21:25:46 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_has_wall(t_data *data, double x, double y)
{
	double	mapx;
	double	mapy;

	if (x < 0 || x > HEIGHT_WIN || y < 0 || y > WIDTH_WIN)
		return (0);
	mapx = floor(x / TILE_SIZE);
	mapy = floor(y / TILE_SIZE);
	if ((data->map[(int)mapx][(int)floor(data->player.pos_x / TILE_SIZE)] != '0' \
		&& data->map[(int)mapx][(int)floor(data->player.pos_x / TILE_SIZE)] != 'N') \
		&& (data->map[(int)floor(data->player.pos_y / TILE_SIZE)][(int)mapy] != '0' \
		&& data->map[(int)floor(data->player.pos_y / TILE_SIZE)][(int)mapy] != 'N'))
		return (1);
	return (data->map[(int)mapx][(int)mapy] != '0' \
		&& data->map[(int)mapx][(int)mapy] != 'N');
}

void	ft_player_right(t_data *data)
{
	double	newposx;
	double	newposy;

	newposy = data->player.pos_x + cos(data->player.rotationangl \
		+ (M_PI / 2)) * data->player.movespeed;
	newposx = data->player.pos_y + sin(data->player.rotationangl \
		+ (M_PI / 2)) * data->player.movespeed;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.pos_y = newposx;
		data->player.pos_x = newposy;
	}
}

void	ft_player_left(t_data *data)
{
	double	newposx;
	double	newposy;

	newposy = data->player.pos_x + cos(data->player.rotationangl \
		- (M_PI / 2)) * data->player.movespeed;
	newposx = data->player.pos_y + sin(data->player.rotationangl \
		- (M_PI / 2)) * data->player.movespeed;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.pos_y = newposx;
		data->player.pos_x = newposy;
	}
}

void	ft_player_up(t_data *data)
{
	double	movestep;
	double	newposx;
	double	newposy;

	movestep = data->player.movespeed * data->player.walkdirection;
	newposy = data->player.pos_x + cos(data->player.rotationangl) * movestep;
	newposx = data->player.pos_y + sin(data->player.rotationangl) * movestep;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.pos_y = newposx;
		data->player.pos_x = newposy;
	}
}

void	ft_player_down(t_data *data)
{

	double	movestep;
	double	newposx;
	double	newposy;

	movestep = data->player.movespeed * data->player.walkdirection;
	newposy = data->player.pos_x + cos(data->player.rotationangl) * movestep;
	newposx = data->player.pos_y + sin(data->player.rotationangl) * movestep;
	if (!ft_has_wall(data, newposx, newposy))
	{
		data->player.pos_y = newposx;
		data->player.pos_x = newposy;
	}
}
