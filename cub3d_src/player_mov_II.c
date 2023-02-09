/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov_II.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:07:00 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/09 14:39:47 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

int	ft_player_movement(t_data *data)
{
	mlx_clear_window(data->mlx.mx, data->mlx.mlx_win);
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
	data->player.rotationangl = fmod(data->player.rotationangl, (2 * M_PI));
	if (data->player.rotationangl < 0)
		data->player.rotationangl += (2 * M_PI);
	ft_put_image_to_win(data);
	return (0);
}
