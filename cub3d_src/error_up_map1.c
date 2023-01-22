/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_up_map1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 00:03:37 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/14 21:51:14 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_slash(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\n')
		len++;
	return (len);
}

char	*ft_strcpy(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char *) * ft_strlen_slash(src));
	if (!dest)
		return (NULL);
	while (src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_get_map(char *name_map, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	data->all_map = (char **)malloc(sizeof(char *) * (data->line_map + 1));
	if (!data->all_map)
		ft_print_error("Error allocation\n", data);
	fd = open(name_map, O_RDONLY);
	if (fd == -1)
		ft_print_error("the doesn't exist\n", data);
	i = -1;
	line = get_next_line(fd);
	while (++i < data->line_map)
	{
		data->all_map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	data->all_map[i] = NULL;
	close(fd);
}

void	ft_check_error_color(char **tab, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] < '0' || tab[i][j] > '9')
				ft_print_error("Error: the RGB color must be digit", data);
			j++;
		}
		i++;
	}
}

void	ft_convert_to_int(char **tab, t_data *data)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
			ft_print_error("Error: out of range,\
 the range from 0 to 255", data);
		i++;
	}
}
