/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:04:15 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/16 18:27:29 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

int	ft_has_wall(t_data *data, double x, double y)
{
	int	new_x;
	int	new_y;
	int	old_x;
	int	old_y;

	if (x <= 0 || x > data->len * TILE_SIZE \
		|| y <= 0 || y > data->line_max * TILE_SIZE)
		return (1);
	new_x = (int)floor(x / TILE_SIZE);
	new_y = (int)floor(y / TILE_SIZE);
	old_x = (int)floor(data->player.pos_x / TILE_SIZE);
	old_y = (int)floor(data->player.pos_y / TILE_SIZE);
	if ((data->map[new_x][old_x] != '0' && (data->map[new_x][old_x] != 'N' && \
		data->map[new_x][old_x] != 'E' && data->map[new_x][old_x] != 'S' && \
		data->map[new_x][old_x] != 'W')) && (data->map[old_y][new_y] != '0' && \
		(data->map[old_y][new_y] != 'N' && data->map[old_y][new_y] != 'E' && \
		data->map[old_y][new_y] != 'S' && data->map[old_y][new_y] != 'W')))
		return (1);
	return (data->map[new_x][new_y] != '0' \
		&& (data->map[new_x][new_y] != 'N' \
		&& data->map[new_x][new_y] != 'E' \
		&& data->map[new_x][new_y] != 'S' \
		&& data->map[new_x][new_y] != 'W'));
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
