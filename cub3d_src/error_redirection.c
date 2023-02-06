/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:11:02 by ibenmain          #+#    #+#             */
/*   Updated: 2023/02/06 20:08:15 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_character(char c, t_data *data)
{
	if (c == 'N')
	{
		data->dir.x += 1;
		data->dir.n += 1;
	}
	else if (c == 'S')
	{
		data->dir.x += 1;
		data->dir.s += 1;
	}
	else if (c == 'W')
	{
		data->dir.x += 1;
		data->dir.w += 1;
	}
	else if (c == 'E')
	{
		data->dir.x += 1;
		data->dir.e += 1;
	}
	if (c != '0' && c != '1' && c != ' ' && c != 'N' \
		&& c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

void	ft_check_direction(t_data *data)
{
	if (data->dir.x != 1)
		ft_print_error("Error: character must be one direction\n", data);
}

void	ft_check_char_dup(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][0] == '0' ||
				ft_check_character(data->map[i][j], data))
				ft_print_error("Error: invalid character\n", data);
			j++;
		}
		i++;
	}
	ft_check_direction(data);
}

void	ft_check_background(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' && (data->map[i][j - 1] == ' '
				|| data->map[i][j + 1] == ' ' || data->map[i - 1][j] == ' '
					|| data->map[i + 1][j] == ' '))
				ft_print_error("Error: invalid character (spaces)\n", data);
			j++;
		}
		i++;
	}
}

void	ft_check_redirection(t_data *data)
{
	data->dir.x = 0;
	if (ft_check_wall(data))
		ft_print_error("Error: invalid map\n", data);
	ft_check_char_dup(data);
	ft_check_background(data);
}
