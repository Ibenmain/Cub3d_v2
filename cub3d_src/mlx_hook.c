/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:55:59 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/21 19:00:16 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_loop(t_data *data)
{
	mlx_hook(data->mlx.mlx_win, 02, 1L << 0, key_pressed, data);
	mlx_hook(data->mlx.mlx_win, 03, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx.mx, &ft_player_movement, data);
	mlx_loop(data->mlx.mx);
}
