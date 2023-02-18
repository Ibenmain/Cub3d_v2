/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:53:25 by nmoussam          #+#    #+#             */
/*   Updated: 2023/02/17 23:58:15 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_free(data->map);
	free(data->rays);
	ft_free(data->all_map);
	free(data);
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

char	*ft_dup_with_space(char *line, t_data *data)
{
	char	*tab;
	int		i;
	int		j;

	tab = (char *)malloc(sizeof(char *) * data->biggest_line + 1);
	if (!tab)
		ft_print_error("error allocation\n");
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

char	*ft_concat(char *s1, char *s2)
{
	int		i;
	int		j;
	int		size_s1;
	int		size_s2;
	char	*new;

	if (!s1)
		s1 = ft_strdup("");
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	new = (char *)malloc((size_s1 + size_s2) + 1 * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size_s1)
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size_s2)
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}
