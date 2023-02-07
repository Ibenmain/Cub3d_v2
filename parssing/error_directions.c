/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 22:43:33 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/20 16:13:35 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_wall(t_data *data)
{
	char	*line;
	char	*line2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!data->map[0])
		ft_print_error("Error: messing map\n", data);
	line = data->map[0];
	line2 = data->map[data->j - 1];
	if (line[0] != '1' && line[0] != ' ')
		return (1);
	while (line[i] && line2[j])
	{
		if ((line[i] != '1' && line[i] != ' ') \
			|| (line2[j] != '1' && line2[j] != ' '))
			return (1);
		i++;
		j++;
	}
	return (0);
}

void	ft_get_max_line(t_data *data)
{
	int	start;

	start = data->i;
	data->biggest_line = 0;
	while (data->all_map[start])
	{
		if (ft_strlen(data->all_map[start]) > data->biggest_line)
			data->biggest_line = ft_strlen(data->all_map[start]);
		start++;
	}
}

void	ft_print_error(char *str, void	*data)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	free(data);
	exit(1);
}

int	ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '1' || line[i] == ' '))
		i++;
	if (i && line[i] == '\n')
		return (1);
	return (0);
}

void	ft_parssing_map(t_data *data)
{
	int		j;

	data->i = 0;
	data->map1.nb_dir = 0;
	ft_initialisation_var(data);
	while (data->all_map[data->i])
	{
		j = 0;
		if (ft_check_line(data->all_map[data->i]))
			break ;
		else if (data->all_map[data->i][0] != '\n')
		{
			while (data->all_map[data->i][j] == ' ')
				j++;
			ft_passing_error(data, data->all_map[data->i] + j);
			data->map1.nb_dir += 1;
		}
		data->i++;
	}
}
