/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:30:20 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/09 15:46:22 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/cub3d.h"

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

int	get_line_map(t_data *data)
{
	int	line;
	int	i;

	i = 0;
	line = 0;
	data->line_max = 0;
	while (data->map[i])
	{
		if (data->line_max < ft_strlen(data->map[i]))
			data->line_max = ft_strlen(data->map[i]);
		line += 1;
		i++;
	}
	return (line);
}

// void	my_mlx_pixel_put1(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x >= 0 && x < data->line_max * TILE_SIZE \
// 		&& y >= 0 && y < data->len * TILE_SIZE)
// 	{
// 		dst = data->img.addr + (y * data->img.line_length + x * \
// 			(data->img.bits_per_pixel / 8));
// 		*(unsigned int *)dst = color;
// 	}
// }

void	DDA(double X0, double Y0, double X1, double Y1, t_data *data)
{
    double dx;
    double dy;
	double steps;
    double xIncrement;
  	double yIncrement;
    double x;
  	double y;
	
	dx = X1 - X0;
	dy = Y1 - Y0;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	xIncrement = dx / steps;
	yIncrement = dy / steps;
	x = X0;
	y = Y0;
    for (int i = 0; i <= steps ; i++) {
        my_mlx_pixel_put(data, round(x), round(y), 0xFFFFCC);
        x += xIncrement; 
        y += yIncrement;		
    }
}

void	draw_rect(t_data *data)
{
	int	i;
	int	j;

	i = 0 ;
	while (i < data->len * TILE_SIZE)
	{
		j = 0;
		while (j < (data->line_max - 1) * TILE_SIZE)
		{
			if (i == 0 || i + 1== (data->len) * TILE_SIZE)
				my_mlx_pixel_put(data, j, i, 0x000000);
			if (j == 0 || j + 1 == (data->line_max - 1) * TILE_SIZE)
				my_mlx_pixel_put(data, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	generate_projection(t_data *data)
{
	int	i;
	int	j;
	int	wall_strip_height;
	int	wall_top_pixl;
	int	wall_botton_pixl;
	
	i = 0;
	while (i < data->player.num_ray)
	{
		data->perp_disc = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player.rotationangl);
		data->disc_proj_plane = (WIDTH_WIN / 2) / tan(data->player.fov_angle / 2);
		data->proj_wall_height = (TILE_SIZE / data->perp_disc) * data->disc_proj_plane;
		wall_strip_height = (int)data->proj_wall_height;
		wall_top_pixl = (HEIGHT_WIN / 2) - (wall_strip_height / 2);
		wall_top_pixl = wall_top_pixl < 0 ? 0 : wall_top_pixl;
		wall_botton_pixl = (HEIGHT_WIN / 2) + (wall_strip_height / 2);
		wall_botton_pixl = wall_botton_pixl > HEIGHT_WIN ? HEIGHT_WIN : wall_botton_pixl;
		j = wall_top_pixl - 1;
		while (j++ < wall_botton_pixl)
			my_mlx_pixel_put1(data,i, j ,0xFFFFFF);
		i++;
	}
}

void	ft_mlx_clear_window(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (i++ < HEIGHT_WIN)
	{
		j = -1;
		while (++j < WIDTH_WIN)
			my_mlx_pixel_put1(data, j, i, 0x000000);
		
	}	
}

int	ft_put_image_to_win(t_data *data)
{
	ft_mlx_clear_window(data);
	data->img.img = mlx_new_image(data->mlx.mx, data->line_max \
		* TILE_SIZE, data->len * TILE_SIZE);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	generate_projection(data);
	ft_draw_map(data);
	draw_circle(data, data->player.pos_y, data->player.pos_x, 0xFF0000);
	ft_cast_rays(data);
	draw_rect(data);
	draw_line(data, data->player.pos_y, data->player.pos_x, 0xFF0000);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, data->img1.img1, 0, 0);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, data->img.img, 0, 0);
	return (0);
}
