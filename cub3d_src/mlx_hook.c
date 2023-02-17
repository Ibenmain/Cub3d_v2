/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:55:59 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/17 22:44:06 by ibenmain         ###   ########.fr       */
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

// int	handle_mouse(int x, int y, t_data *data)
// {
// 	mlx_clear_window(data->var.mlx, data->var.win);
// 	(void)y;
// 	if (data->mouse != 1e15)
// 	{
// 		if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
// 		{
// 			if (data->mouse < x)
// 				data->ply.turn_dir = -1;
// 			else
// 				data->ply.turn_dir = 1;
// 			data->ply.rotation_angle += (data->ply.turn_dir \
// 			* 0.02);
// 			data->mouse = x;
// 		}
// 		render(data);
// 	}
// 	else
// 		data->mouse = x;
// 	return (0);
// }

int	_handler_mouse(int y, int x, t_data *data)
{
	mlx_clear_window(data->mlx.mx, data->mlx.mlx_win);
	if (x > 0 && x < WIDTH_WIN && y > 0 && y < HEIGHT_WIN)
	{
		if (x > data->mouse)
			key_pressed(RIGHT_KEY, data);
		else
			key_pressed(LEFT_KEY, data);
	}
	data->mouse = x;
	ft_put_image_to_win(data);
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
