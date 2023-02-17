/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:24:59 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/17 23:37:34 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft_cub/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# define BUFFER_SIZE 1024

# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
# define ESC_KEY 53
# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53

# define WIDTH_WIN 1920
# define HEIGHT_WIN 1080
# define TILE_SIZE 10
# define TURNDIRECTION 0
# define WALKDIRECTION 0
# define MOVESPEED 2.0

enum
{
	NO,
	SO,
	WE,
	EA,
};

typedef struct s_map1
{
	int		no_dup;
	int		so_dup;
	int		we_dup;
	int		ea_dup;
	char	*no_line;
	char	*no_path;
	char	*so_line;
	char	*so_path;
	char	*we_line;
	char	*we_path;
	char	*ea_line;
	char	*ea_path;
	char	*floor_line;
	char	*color_line;
	int		f_dup;
	int		c_dup;
}				t_map1;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_dir{
	char	n;
	char	s;
	char	w;
	char	e;
	int		x;
}		t_dir;

typedef struct s_mlx{
	void	*mx;
	void	*mlx_win;
}		t_mlx;

typedef struct s_player{
	double	pos_x;
	double	pos_y;
	double	rotationangl; // related to view direction of player ()
	double	sidedirection;
	double	walkdirection; // -1 if back, 1 if front
	double	turndirection; // -1 if left, 1 if right
	double	rotationspeed; // speed you want player turn to left or right
	double	movespeed; // speed of player
	double	fov_angle;
	double	num_ray;
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distanc;
	double	is_rayfacing_down;
	double	is_rayfacing_up;
	double	is_rayfacing_left;
	double	is_rayfacing_right;
}		t_player;

typedef struct s_ray{
	double	next_hor_x;
	double	next_hor_y;
	double	found_wall_h;
	double	wall_hit_hor_x;
	double	wall_hit_hor_y;
	double	xintercept_hor;
	double	yintercept_hor;
	//*********************************//
	double	next_ver_x;
	double	next_ver_y;
	double	found_wall_v;
	double	wall_hit_ver_x;
	double	wall_hit_ver_y;
	double	xintercept_ver;
	double	yintercept_ver;
}		t_ray;

typedef struct s_rays{
	double	distance;
	double	pos_ray_x;
	double	pos_ray_y;
	double	ray_angle;
	int		ver_hor;
	int		dir_up;
	int		dir_down;
	int		dir_left;
	int		dir_right;
	int		textur_offset_x;
	int		textur_offset_y;
	int		wall_strip_height;
	int		wall_top_pixl;
	int		wall_bottom_pixl;
}		t_rays;

typedef struct s_data{
	char			**all_map;
	char			**map_dir;
	char			**map;
	int				line_max;
	int				len;
	int				line_map;
	int				i;
	int				j;
	int				biggest_line;
	int				val1_f;
	int				val2_f;
	int				val3_f;
	int				val1_c;
	int				val2_c;
	int				val3_c;
	double			perp_disc;
	double			disc_proj_plane;
	double			proj_wall_height;
	double			xincrement;
	double			yincrement;
	double			steps;
	double			dx;
	double			dy;
	double			mouse;
	t_map1			map1;
	t_dir			dir;
	t_mlx			mlx;
	t_img			img_mini;
	t_img			img_3d;
	t_img			img_dir[4];
	t_player		player;
	t_ray			ray;
	t_rays			*rays;
}		t_data;

char	*get_next_line(int fd);
int		find_new_line(char *string);
char	*get_line(char *str);
char	*get_rest(char *str);
char	*ft_concat(char *s1, char *s2);
void	ft_get_map(char *name_map, t_data *data);
void	ft_map_size(char *map, t_data *data);
void	ft_divide_down_map(t_data *data);
int		ft_check_name_map(char *map_name);
void	ft_print_error(char *str);
int		ft_check_line(char *line);
int		ft_check_error_tab(char **tab);
void	ft_directione(char **tab, t_data *data);
void	ft_range_of_color(char *val, char *line, t_data *data);
void	ft_color_and_floor(char **tab, t_data *data);
void	ft_free(char	**tab);
void	ft_convert_to_int(char **tab);
void	ft_check_error_color(char **tab);
void	ft_passing_error(t_data *data, char *line);
void	ft_parssing_map(t_data *data);
void	ft_check_duplicat(t_data *data);
void	ft_get_max_line(t_data *data);
void	ft_check_redirection(t_data *data);
int		ft_check_wall(t_data *data);
char	*ft_duplicat(char *str, t_data *data);
char	*ft_dup_with_space(char *line, t_data *data);
int		ft_cub3d(int ac, char **av, t_data *data);
int		ft_mlx_wind(t_data *data);
int		get_line_map(t_data *data);
int		ft_check_spase(char *line);
int		get_line_map(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put1(t_data *data, int x, int y, int color);
void	draw_rectangle(int x, int y, t_data *data, int color);
int		ft_put_image_to_win(t_data *data);
void	draw_circle(t_data *data, int x, int y, int r);
void	draw_line(t_data *data, int x, int y, int color);
void	ft_initialisation_var(t_data *data);
void	ft_position_player(t_data *data);
int		ft_player_movement(t_data *data);
int		key_pressed(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	ft_init_player(t_data *data);
void	ft_mlx_loop(t_data *data);
int		ft_has_wall(t_data *data, double x, double y);
void	ft_player_left(t_data *data);
void	ft_player_right(t_data *data);
void	ft_player_up(t_data *data);
void	ft_player_down(t_data *data);
int		ft_has_wall(t_data *data, double x, double y);
double	ft_normalizeangle(double rayangle);
void	ft_ray_cast_hor(t_data *data, double ray_angle);
void	ft_ray_cast_ver(t_data *data, double ray_angle);
void	draw_circle(t_data *data, int x, int y, int color);
void	draw_rectangle(int x, int y, t_data *data, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_draw_map(t_data *data);
void	dda(double X1, double Y1, t_data *data);
void	ft_cast_rays(t_data *data);
int		_is_wall(double next_hor_x, double next_hor_y, t_data *data);
int		ft_get_direction(t_data *data, int i);
int		create_trgb(int t, int r, int g, int b);
void	draw_rect(t_data *data);
void	generate_projection(t_data *data);
void	ft_rander_wall_strip(t_data *data, int i);
int		ft_check_spase_in_line(char *str);
void	ft_free_all_data(t_data *data);
int		parssing(int ac, char **av, t_data *data);
void	execution(t_data *data);
#endif