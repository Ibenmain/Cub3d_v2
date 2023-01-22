/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:48:13 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/10 14:32:24 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *str, char d)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] != d)
		count = 1;
	else
		count = 0;
	while (str[i])
	{
		if (str[i] && str[i] == d && str[i + 1] != d && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	_free(char **tab)
{
	while (*tab)
		free(*tab);
	free(tab);
}

static char	**ft_other_split(char const *s, char c, int i, int j)
{
	char	**tab;
	int		start;
	int		end;

	if (!s)
		return (NULL);
	tab = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > 0 && s[end -1] != c)
		{
			tab[j++] = ft_substr(s, start, end - start);
			if (!tab[j - 1])
				return (_free(tab), NULL);
		}
	}
	return (tab[j] = NULL, tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = ft_other_split(s, c, i, j);
	return (tab);
}
