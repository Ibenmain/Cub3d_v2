/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:43:50 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/20 16:10:31 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_check_path(char **tab, t_data *data)
{
	int		fd;
	int		len;
	char	*path;

	path = ft_strcpy(tab[1]);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_print_error("file doesn't exist\n", data);
	close (fd);
	len = ft_strlen(path);
	if (path[len - 4] != '.' || path[len - 3] != 'x' || \
		path[len - 2] != 'p' || path[len - 1] != 'm' )
		ft_print_error("the extention must be .xpm\n", data);
	if (!ft_strcmp(tab[0], "NO"))
		data->map1.no_line = tab[0];
	else if (ft_strcmp(tab[0], "SO"))
		data->map1.so_line = tab[0];
	else if (ft_strcmp(tab[0], "WE"))
		data->map1.we_line = tab[0];
	else if (ft_strcmp(tab[0], "EA"))
		data->map1.ea_line = tab[0];
	return (path);
}

void	ft_directione(char **tab, t_data *data)
{
	if (!ft_strcmp(tab[0], "NO"))
	{
		data->map1.no_path = ft_check_path(tab, data);
		data->map1.no_dup += 1;
	}
	else if (!ft_strcmp(tab[0], "SO"))
	{
		data->map1.so_path = ft_check_path(tab, data);
		data->map1.so_dup += 1;
	}
	else if (!ft_strcmp(tab[0], "WE"))
	{
		data->map1.we_path = ft_check_path(tab, data);
		data->map1.we_dup += 1;
	}
	else if (!ft_strcmp(tab[0], "EA"))
	{
		data->map1.ea_path = ft_check_path(tab, data);
		data->map1.ea_dup += 1;
	}
	else
		ft_print_error("Error: invalid map\n", data);
}

void	ft_passing_error(t_data *data, char *line)
{
	char	**tab;
	int		len;
	int		size;

	len = ft_strlen(line);
	if (line[0] == '\n' || line[len - 2] == ' ')
		ft_print_error("Error: invalid a map", data);
	tab = ft_split(line, ' ');
	size = ft_check_error_tab(tab);
	if (size != 2)
		ft_print_error("Error: invalid map", data);
	if (ft_strlen(tab[0]) == 2)
		ft_directione(tab, data);
	else if (ft_strlen(tab[0]) == 1)
		ft_color_and_floor(tab, data);
	else
		ft_print_error("Error: invalid map", data);
}

void	ft_check_duplicat(t_data *data)
{
	if (data->map1.no_dup != 1 || data->map1.so_dup != 1 || data->map1.we_dup \
		!= 1 || data->map1.ea_dup != 1 || data->map1.c_dup != 1 \
		|| data->map1.f_dup != 1)
		ft_print_error("Error: some texture duplicated", data);
}
