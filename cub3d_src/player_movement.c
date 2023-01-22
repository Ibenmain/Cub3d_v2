/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:04:15 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/21 22:27:03 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player_left(t_data *data)
{
	data->player.i += cos(data->player.rotationangl \
		+ 90 * (M_PI / 180)) * data->player.movespeed;
	data->player.j += sin(data->player.rotationangl \
		+ 90 * (M_PI / 180)) * data->player.movespeed;
}

void	ft_player_right(t_data *data)
{
	data->player.i += cos(data->player.rotationangl \
		-90 * (M_PI / 180)) * data->player.movespeed;
	data->player.j += sin(data->player.rotationangl \
		-90 * (M_PI / 180)) * data->player.movespeed;
}

void	ft_player_up(t_data *data)
{
	double	movestep;

	movestep = data->player.movespeed * data->player.walkdirection;
	data->player.i += cos(data->player.rotationangl) * movestep;
	data->player.j += sin(data->player.rotationangl) * movestep;
}

void	ft_player_down(t_data *data)
{
	double	movestep;

	movestep = data->player.movespeed * data->player.walkdirection;
	data->player.i += cos(data->player.rotationangl) * movestep;
	data->player.j += sin(data->player.rotationangl) * movestep;
}

int	ft_player_movement(t_data *data)
{
	if (data->player.walkdirection == 1)
		ft_player_up(data);
	if (data->player.walkdirection == -1)
		ft_player_down(data);
	if (data->player.sidedirection == -1)
		ft_player_left(data);
	if (data->player.sidedirection == 1)
		ft_player_right(data);
	if (data->player.turndirection == -1)
		data->player.rotationangl += data->player.rotationspeed \
			* data->player.turndirection;
	if (data->player.turndirection == 1)
		data->player.rotationangl += data->player.rotationspeed \
			* data->player.turndirection;
	ft_put_image_to_win(data);
	return (0);
}
