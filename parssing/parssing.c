/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:52:04 by nmoussam          #+#    #+#             */
/*   Updated: 2023/02/18 00:05:45 by ibenmain         ###   ########.fr       */
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
		ft_print_error("file doesn't exist\n");
	close (fd);
	len = ft_strlen(path);
	if (path[len - 4] != '.' || path[len - 3] != 'x' || \
		path[len - 2] != 'p' || path[len - 1] != 'm' )
		ft_print_error("the extention must be .xpm\n");
	if (!ft_strcmp(tab[0], "NO"))
		data->map1.no_line = ft_strdup(tab[0]);
	else if (!ft_strcmp(tab[0], "SO"))
		data->map1.so_line = ft_strdup(tab[0]);
	else if (!ft_strcmp(tab[0], "WE"))
		data->map1.we_line = ft_strdup(tab[0]);
	else if (!ft_strcmp(tab[0], "EA"))
		data->map1.ea_line = ft_strdup(tab[0]);
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
		ft_print_error("error: invalid map\n");
}

void	ft_passing_error(t_data *data, char *line)
{
	char	**tab;
	int		len;
	int		size;

	len = ft_strlen(line);
	if (line[len - 2] == ' ')
		ft_print_error("error: invalid a map\n");
	tab = ft_split(line, ' ');
	size = ft_check_error_tab(tab);
	if (size != 2)
		ft_print_error("error: invalid map\n");
	if (ft_strlen(tab[0]) == 2)
		ft_directione(tab, data);
	else if (ft_strlen(tab[0]) == 1)
		ft_color_and_floor(tab, data);
	else
		ft_print_error("error: invalid map\n");
	ft_free(tab);
}

void	ft_check_duplicat(t_data *data)
{
	if (data->map1.no_dup != 1 || data->map1.so_dup != 1 || data->map1.we_dup \
		!= 1 || data->map1.ea_dup != 1 || data->map1.c_dup != 1 \
		|| data->map1.f_dup != 1)
		ft_print_error("error: invalid map\n");
}

char	*ft_duplicat(char *str, t_data *data)
{
	char	*tab;
	int		i;

	tab = (char *)malloc(sizeof(char *) * data->biggest_line + 1);
	if (!tab)
		ft_print_error("error allocation\n");
	i = 0;
	while (str[i] != '\n')
	{
		tab[i] = str[i];
		i++;
	}
	tab[i++] = ' ';
	tab[i] = '\0';
	return (tab);
}
