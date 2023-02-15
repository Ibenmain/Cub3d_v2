/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:53:04 by nmoussam          #+#    #+#             */
/*   Updated: 2023/02/15 13:53:05 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_name_map(char *map_name)
{
	int	len;
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (1);
	len = ft_strlen(map_name);
	if (map_name[len - 4] == '.' && map_name[len - 3] == 'c' && \
		map_name[len - 2] == 'u' && map_name[len - 1] == 'b')
		return (0);
	return (1);
}

void	ft_map_size(char *map, t_data *data)
{
	int		fd;
	char	*line;

	data->line_map = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_print_error("can't open file\n", data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->line_map += 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
}

void	ft_free(char	**tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_check_error_tab(char **tab)
{
	int	nb;

	nb = 0;
	while (tab[nb] != NULL)
		nb++;
	return (nb);
}

int	ft_check_spase_in_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (i && str[i] == '\0')
		return (1);
	return (0);
}

void	ft_divide_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		if (ft_check_spase_in_line(data->map[i]))
			ft_print_error("error: invalid map", data);
		i++;
	}
}

void	ft_free_all_data(t_data *data)
{
	free(data->map1.no_line);
	free(data->map1.so_line);
	free(data->map1.we_line);
	free(data->map1.ea_line);
	free(data->map1.no_path);
	free(data->map1.so_path);
	free(data->map1.we_path);
	free(data->map1.ea_path);
	ft_free(data->all_map);
	ft_free(data->map);
	free(data->rays);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac != 2 || ft_check_name_map(av[1]))
		return (free(data), printf("error: invalid arguments!\n"), 1);
	ft_map_size(av[1], data);
	ft_get_map(av[1], data);
	ft_parssing_map(data);
	ft_check_duplicat(data);
	ft_get_max_line(data);
	ft_divide_down_map(data);
	ft_check_redirection(data);
	ft_divide_map(data);
	ft_init_player(data);
	ft_cub3d(data);
	ft_free_all_data(data);
	return (0);
}
