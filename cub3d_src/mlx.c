/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:30:20 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/01 20:26:24 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	my_mlx_pixel_put1(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 35 * TILE_SIZE  && y >= 0 && y < 15 * TILE_SIZE)
	{
		dst = data->img.addr + (y * data->img.line_length + x * \
			(data->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH_WIN  && y >= 0 && y < HEIGHT_WIN)
	{
		dst = data->img.addr + (y * data->img.line_length + x * \
			(data->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_rectangle(int x, int y, t_data *data, int color)
{
	int	i;
	int	j;

	i = x * TILE_SIZE;
	while (i < x * TILE_SIZE + TILE_SIZE)
	{
		j = y * TILE_SIZE;
		while (j < y * TILE_SIZE + TILE_SIZE)
		{
			if (i % TILE_SIZE == 0 || j % TILE_SIZE == 0)
				my_mlx_pixel_put(data, j, i, 0x00404040);
			else
				my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->len)
	{
		j = -1;
		while (++j < data->line_max)
		{
			if (data->map[i][j] != ' ')
			{
				if (data->map[i][j] == '1')
					draw_rectangle(i, j, data, 0x000066CC);
				else
					draw_rectangle(i, j, data, 0x00CCCCFF);
			}
		}
	}
}

void DDA(double X0, double Y0, double X1, double Y1, t_data *data)
{

    double dx = X1 - X0;
    double dy = Y1 - Y0;
    
	double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    
    double xIncrement = dx / steps;
  	double yIncrement = dy / steps;
    
    double x = X0;
  	double y = Y0;
    for (int i = 0; i <= steps ; i++) {
        my_mlx_pixel_put1(data, round(x), round(y), 0xFF0000);
        x += xIncrement; 
        y += yIncrement; 
		
    }
}

void	ft_horizontal(double xstep, double ystep, t_data *data)
{
	data->ray.next_hor_x = data->ray.xintercept_hor;
	data->ray.next_hor_y = data->ray.yintercept_hor;
	if(data->player.is_rayfacing_up)
		data->ray.next_hor_y--;
	// we just increment xstep and ystep until we find a wall
	while (data->ray.next_hor_x >= 0 && data->ray.next_hor_x < 35 * TILE_SIZE \
		&& data->ray.next_hor_y >= 0 && data->ray.next_hor_y < 15 * TILE_SIZE)
	{
		if (data->map[(int)(data->ray.next_hor_y / TILE_SIZE)][(int)(data->ray.next_hor_x / TILE_SIZE)] == '1')
		{
			data->ray.found_wall_h = 1;
			data->ray.wall_hit_hor_x = data->ray.next_hor_x;
			data->ray.wall_hit_hor_y = data->ray.next_hor_y;
			break ;
		}
		data->ray.next_hor_x += xstep;
		data->ray.next_hor_y += ystep;
	}
}

void	ft_ray_cast_hor(t_data *data, double ray_angle)
{
	double	xstep;
	double	ystep;

	// find the y-coordinat of the closest horizontal grid intersection
	data->ray.yintercept_hor = floor(data->player.pos_y / TILE_SIZE) * TILE_SIZE;
	// if the rayfacing down must add TILE_SIZE to yintercept if not don't do enything
	if (data->player.is_rayfacing_down)
		data->ray.yintercept_hor += TILE_SIZE;
	// find the x-coordinat of the closest horizontal grid intersection
	data->ray.xintercept_hor = data->player.pos_x + ((data->ray.yintercept_hor	\
		- data->player.pos_y) / tan(ray_angle));
	// calculat the xstep and ystep (next step)
	ystep = TILE_SIZE;
	// increment or deincremenrt ystep of player 
	if (data->player.is_rayfacing_up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(ray_angle);
	if (data->player.is_rayfacing_left && xstep > 0)
		xstep *= -1;
	if (data->player.is_rayfacing_right && xstep < 0)
		xstep *= -1;
	ft_horizontal(xstep, ystep, data);
}

void	ft_verticale(double xstep, double ystep, t_data *data)
{
	data->ray.next_ver_x = data->ray.xintercept_ver;
	data->ray.next_ver_y = data->ray.yintercept_ver;
	if(data->player.is_rayfacing_left)
		data->ray.next_ver_x--;
	// we just increment xstep and ystep until we find a wall
	while (data->ray.next_ver_x >= 0 && data->ray.next_ver_x < 35 * TILE_SIZE \
		&& data->ray.next_ver_y >= 0 && data->ray.next_ver_y < 15 * TILE_SIZE)
	{
		if (data->map[(int)(data->ray.next_ver_y / TILE_SIZE)][(int)(data->ray.next_ver_x / TILE_SIZE)] == '1')
		{
			data->ray.found_wall_v = 1;
			data->ray.wall_hit_ver_x = data->ray.next_ver_x;
			data->ray.wall_hit_ver_y = data->ray.next_ver_y;
			break ;
		}
		data->ray.next_ver_x += xstep;
		data->ray.next_ver_y += ystep;
	}
	
}

void	ft_ray_cast_ver(t_data *data, double ray_angle)
{
	double	xstep;
	double	ystep;
	
	// find the x-coordinat of the closest verticale grid intersection
	data->ray.xintercept_ver = floor(data->player.pos_x / TILE_SIZE) * TILE_SIZE;
	// if the rayfacing right must add TILE_SIZE to yintercept if not don't do enything
	if (data->player.is_rayfacing_right)
		data->ray.xintercept_ver += TILE_SIZE;
	// find the y-coordinat of the closest verticale grid intersection
	data->ray.yintercept_ver = data->player.pos_y + ((data->ray.xintercept_ver - data->player.pos_x) * tan(ray_angle));
	// calculat the xstep and ystep (next step)
	xstep = TILE_SIZE;
	if (data->player.is_rayfacing_left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(ray_angle);
	if (data->player.is_rayfacing_up && ystep > 0)
		ystep *= -1;
	if (data->player.is_rayfacing_down && ystep < 0)
		ystep *= -1;
	ft_verticale(xstep, ystep, data);
}

int	calcule_dis(t_data *data)
{
	double	ver_dis;
	double	hor_dis;

	// we need get the smaller distanc between horizontal & vertical
	ver_dis = sqrt(pow((data->player.pos_x - data->ray.wall_hit_ver_x), 2) + pow((data->player.pos_y - data->ray.wall_hit_ver_y), 2));
	hor_dis = sqrt(pow((data->player.pos_x - data->ray.wall_hit_hor_x), 2) + pow((data->player.pos_y - data->ray.wall_hit_hor_y), 2));
	if (ver_dis <= hor_dis)
		return (1);
	return (0);
}

void	ft_initial_var(t_data *data)
{
	data->ray.next_hor_x = 0;
	data->ray.next_hor_y = 0;
	data->ray.wall_hit_hor_x = WIDTH_WIN;
	data->ray.wall_hit_hor_y = WIDTH_WIN;
	data->ray.yintercept_hor = 0;
	data->ray.xintercept_hor = 0;
	data->ray.found_wall_h = 0;
	data->player.is_rayfacing_up = 0;
	data->player.is_rayfacing_down = 0;
	data->player.is_rayfacing_left = 0;
	data->player.is_rayfacing_right = 0;
	data->ray.next_ver_x = 0;
	data->ray.next_ver_y = 0;
	data->ray.wall_hit_ver_x = WIDTH_WIN;
	data->ray.wall_hit_ver_y = WIDTH_WIN;
	data->ray.yintercept_ver = 0;
	data->ray.xintercept_ver = 0;
	data->ray.found_wall_v = 0;
}

void	ft_determine_the_trends(double rayangle, t_data *data)
{
	if (rayangle > 0 && rayangle < M_PI)
		data->player.is_rayfacing_down = 1;
	else
		data->player.is_rayfacing_up = 1;
	if (rayangle <= M_PI_2 || rayangle >= (3 * M_PI_2))
		data->player.is_rayfacing_right = 1;
	else
		data->player.is_rayfacing_left = 1;
}

void	ft_cast_rays(t_data *data)
{
	double rayangle;
	int i = 0;

	rayangle = data->player.rotationangl - (data->player.fov_angle / 2);
	while (i < data->player.num_ray)
	{
		ft_initial_var(data);
		rayangle = ft_normalizeangle(rayangle);
		ft_determine_the_trends(rayangle, data);
		ft_ray_cast_hor(data, rayangle);
		rayangle = ft_normalizeangle(rayangle);
		ft_ray_cast_ver(data, rayangle);
		rayangle = ft_normalizeangle(rayangle);
		if (calcule_dis(data))
			DDA(data->player.pos_x, data->player.pos_y, data->ray.wall_hit_ver_x, data->ray.wall_hit_ver_y, data);
		else
			DDA(data->player.pos_x, data->player.pos_y, data->ray.wall_hit_hor_x, data->ray.wall_hit_hor_y, data);
		rayangle += data->player.fov_angle / data->player.num_ray;
		i++;
	}
}

int	ft_put_image_to_win(t_data *data)
{
	ft_draw_map(data);
	draw_circle(data, data->player.pos_y, data->player.pos_x, 0x00000000);
	// draw_line(data, data->player.pos_y, data->player.pos_x, 0x000000);
	ft_cast_rays(data);
	mlx_put_image_to_window(data->mlx.mx, data->mlx.mlx_win, \
		data->img.img, 0, 0);
	return (0);
}
