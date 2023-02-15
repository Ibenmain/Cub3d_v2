/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:55:59 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/15 21:54:27 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

void	DDA(double X0, double Y0, double X1, double Y1, t_data *data)
{
	double	xincrement;
	double	yincrement;
	double	steps;
	double	dx;
	double	dy;
	double	x;
	double	y;
	int		i;

	i = 0;
	dx = X1 - X0;
	dy = Y1 - Y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	if (steps == 0)
		return ;
	xincrement = dx / steps;
	yincrement = dy / steps;
	x = X0;
	y = Y0;
	while (i <= steps)
	{
		my_mlx_pixel_put(data, round(x), round(y), 0xFFFFCC);
		x += xincrement;
		y += yincrement;
		i++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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
