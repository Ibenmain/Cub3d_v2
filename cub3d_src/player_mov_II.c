/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov_II.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:07:00 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/23 02:07:18 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
