/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_up_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 00:02:29 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/15 22:50:06 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_dup_space(char *line, t_data *data)
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
		if (line[i + 1] == '\0')
		{
			tab[i] = line[i];
			j = i;
			while (j++ < data->biggest_line - 1)
				tab[j] = ' ';
			tab[j] = '\0';
		}
		else
			tab[i] = line[i];
		i++;
	}
	return (tab);
}

char	*ft_strdup_2(const char *s1)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}	
	new[i] = '\0';
	return (new);
}

char	*ft_line(char *line, t_data *data)
{
	char	*tab;

	tab = NULL;
	if (ft_strlen(line) == data->biggest_line)
	{
		tab = ft_strdup_2(line);
	}
	else
	{
		tab = ft_dup_space(line, data);
	}
	return (tab);
}

char	*ft_check_size_line(char	*line, t_data *data)
{
	char	*tab;

	tab = NULL;
	if (line[ft_strlen(line) - 1] == '\n')
	{
		if (ft_strlen(line) == data->biggest_line)
			tab = ft_duplicat(line, data);
		else
			tab = ft_dup_with_space(line, data);
	}
	else if (line[ft_strlen(line) - 1] != '\n')
	{
		tab = ft_line(line, data);
	}
	return (tab);
}

void	ft_divide_down_map(t_data *data)
{
	data->map = (char **)malloc(sizeof(char *) * \
		((data->line_map - data->i) + 1));
	if (!data->map)
		ft_print_error("Error allocation", data);
	data->j = 0;
	while (data->all_map[data->i])
	{
		data->map[data->j] = ft_check_size_line(data->all_map[data->i], data);
		data->j++;
		data->i++;
	}
	data->map[data->j] = NULL;
}
