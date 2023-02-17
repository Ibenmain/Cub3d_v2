/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_up_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:53:14 by nmoussam          #+#    #+#             */
/*   Updated: 2023/02/17 21:07:42 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_initialisation_var(t_data *data)
{
	data->map1.so_dup = 0;
	data->map1.no_dup = 0;
	data->map1.we_dup = 0;
	data->map1.ea_dup = 0;
	data->map1.f_dup = 0;
	data->map1.c_dup = 0;
}

int	ft_check_virgule(char *path)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (path[i])
	{
		if (path[i] == ',')
			c += 1;
		i++;
	}
	return (c);
}

void	ft_get_color_value(char *val, char **tab, t_data *data)
{
	if (!ft_strcmp(val, "F"))
	{
		data->val1_f = ft_atoi(tab[0]);
		data->val2_f = ft_atoi(tab[1]);
		data->val3_f = ft_atoi(tab[2]);
	}
	else if (!ft_strcmp(val, "C"))
	{
		data->val1_c = ft_atoi(tab[0]);
		data->val2_c = ft_atoi(tab[1]);
		data->val3_c = ft_atoi(tab[2]);
	}
}

void	ft_range_of_color(char *val, char *line, t_data *data)
{
	char	**tab;
	char	*path;
	int		len;

	path = ft_strcpy(line);
	if (ft_check_virgule(path) != 2)
	{
		free(path);
		ft_print_error("error: number of virgule must be equale two\n");
	}
	tab = ft_split(path, ',');
	ft_check_error_color(tab);
	ft_convert_to_int(tab);
	len = ft_check_error_tab(tab);
	if (len != 3)
		ft_print_error("error: the number of RGB\
 must be three separated by comma\n");
	ft_get_color_value(val, tab, data);
	free(path);
	ft_free(tab);
}

void	ft_color_and_floor(char **tab, t_data *data)
{
	if (!ft_strcmp(tab[0], "F"))
	{
		data->map1.floor_line = tab[0];
		data->map1.f_dup += 1;
		ft_range_of_color(tab[0], tab[1], data);
	}
	else if (!ft_strcmp(tab[0], "C"))
	{
		data->map1.color_line = tab[0];
		data->map1.c_dup += 1;
		ft_range_of_color(tab[0], tab[1], data);
	}
	else
		ft_print_error("error: some characters is wrong\n");
}
