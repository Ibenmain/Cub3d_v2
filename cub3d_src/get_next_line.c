/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:29:26 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/06 13:02:18 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_rest(char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	new_str = ft_substr(str, i + 1, (ft_strlen(str) - i) + 1);
	free(str);
	str = NULL;
	return (new_str);
}

char	*get_line(char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	new_str = ft_substr(str, 0, i + 1);
	return (new_str);
}

int	find_new_line(char *string)
{
	int	i;

	if (!string)
		return (0);
	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*str;
	int			size_read;
	char		*line;
	char		buff[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (find_new_line(str) == 1)
		return (line = get_line(str), str = get_rest(str), line);
	size_read = read(fd, buff, BUFFER_SIZE);
	if (size_read <= 0)
	{
		if (!str)
			return (NULL);
		if (!*str)
			return (free(str), str = NULL, NULL);
		line = ft_strdup(str);
		return (free(str), str = NULL, line);
	}
	buff[size_read] = '\0';
	str = ft_concat(str, buff);
	return (get_next_line(fd));
}
