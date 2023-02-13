/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:30:20 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/13 13:45:50 by ibenmain         ###   ########.fr       */
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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	wall_texture(t_data *data)
{
	int	x;
	int	y;
	x = 0;
	while (x < TEXTURE_WIDTH)
	{
		y = 0;
		while (y < TEXTURE_HEIGHT)
		{
			data->wall_texture[(TEXTURE_WIDTH * y) + x] = (x % 8 && y % 8) ? 0xFF0000FF : 0xFF000000;
			y++;
		}
		x++;
	}
}

void	generate_projection(t_data *data)
{
	int	i;
	int	j;
	int	color;
	int	wall_strip_height;
	int	wall_top_pixl;
	int	wall_bottom_pixl;
	int	textur_offset_x;
	int	textur_offset_y;
	// int	distance_from_top;

	i = 0;
	while (i < data->player.num_ray)
	{
		data->perp_disc = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player.rotationangl);
		data->disc_proj_plane = (WIDTH_WIN / 2) / tan(data->player.fov_angle / 2.0);
		data->proj_wall_height = (TILE_SIZE / data->perp_disc) * data->disc_proj_plane;
		wall_strip_height = (int)data->proj_wall_height;
		wall_top_pixl = (HEIGHT_WIN / 2.0) - (wall_strip_height / 2);
		if (wall_top_pixl < 0)
			wall_top_pixl = 0;
		wall_bottom_pixl = (HEIGHT_WIN / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixl > HEIGHT_WIN)
			wall_bottom_pixl = HEIGHT_WIN;
		j = 0;
		while (j++ < wall_top_pixl)
			my_mlx_pixel_put1(data,i, j , create_trgb(0, data->val1_c, data->val2_c, data->val3_c));
		if (data->rays[i].ver_hor)
			textur_offset_x = (data->rays[i].pos_ray_y / TILE_SIZE - (int)(data->rays[i].pos_ray_y) / TILE_SIZE) * TEXTURE_WIDTH;
		else
			textur_offset_x = (data->rays[i].pos_ray_x / TILE_SIZE - (int)(data->rays[i].pos_ray_x) / TILE_SIZE) * TEXTURE_WIDTH;
		j = wall_top_pixl;
		while (j++ < wall_bottom_pixl)
		{
			// distance_from_top = j + (wall_strip_height / 2) - (HEIGHT_WIN / 2);
			textur_offset_y = (j - wall_top_pixl) * ((double)TEXTURE_HEIGHT / wall_strip_height);
			color = *((int *)((data->imgwall.addrwall) + ((int)(textur_offset_y % TEXTURE_HEIGHT) * data->imgwall.line_lengthwall + (int)(textur_offset_x % TEXTURE_WIDTH) * (data->imgwall.bits_per_pixelwall / 8))));
			my_mlx_pixel_put1(data, i, j, color);
		}
		j = wall_bottom_pixl;
		while (j++ < HEIGHT_WIN)
			my_mlx_pixel_put1(data,i, j , create_trgb(0, data->val1_f, data->val2_f, data->val3_f));
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
	ft_draw_map(data);
	draw_rect(data);
	ft_cast_rays(data);
	generate_projection(data);
	draw_circle(data, data->player.pos_y, data->player.pos_x, 0xFF0000);
	draw_line(data, data->player.pos_y, data->player.pos_x, 0xFF0000);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, data->img1.img1, 0, 0);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, data->img.img, 0, 0);
	return (0);
}
