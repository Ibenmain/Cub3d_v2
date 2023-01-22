/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_up_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:37:57 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/20 16:15:25 by ibenmain         ###   ########.fr       */
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

void	ft_range_of_color(char *line, t_data *data)
{
	char	**tab;
	char	*path;
	int		len;

	path = ft_strcpy(line);
	tab = ft_split(path, ',');
	ft_check_error_color(tab, data);
	ft_convert_to_int(tab, data);
	len = ft_check_error_tab(tab);
	if (len != 3)
		ft_print_error("Error: the number of RGB\
 must be three separated by comma", data);
	data->val1 = ft_atoi(tab[0]);
	data->val2 = ft_atoi(tab[1]);
	data->val3 = ft_atoi(tab[2]);
}

void	ft_color_and_floor(char **tab, t_data *data)
{
	if (!ft_strcmp(tab[0], "F"))
	{
		data->map1.floor_line = tab[0];
		data->map1.f_dup += 1;
		ft_range_of_color(tab[1], data);
	}
	else if (!ft_strcmp(tab[0], "C"))
	{
		data->map1.color_line = tab[0];
		data->map1.c_dup += 1;
		ft_range_of_color(tab[1], data);
	}
	else
		ft_print_error("Error: some characters is wrong\n", data);
}

char	*ft_duplicat(char *str, t_data *data)
{
	char	*tab;
	int		i;

	tab = (char *)malloc(sizeof(char *) * data->biggest_line + 1);
	if (!tab)
		ft_print_error("error allocation", data);
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

char	*ft_dup_with_space(char *line, t_data *data)
{
	char	*tab;
	int		i;
	int		j;

	tab = (char *)malloc(sizeof(char *) * data->biggest_line + 1);
	if (!tab)
		ft_print_error("error allocation", data);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			j = i;
			while (j < data->biggest_line)
				tab[j++] = ' ';
			tab[j] = '\0';
		}
		else
			tab[i] = line[i];
		i++;
	}
	return (tab);
}
