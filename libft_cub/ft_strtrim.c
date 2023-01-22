/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:18:47 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/04 15:55:51 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_word(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	while (s1[i] && ft_word(set, s1[i]) == 1)
		i++;
	while (j > i && ft_word(set, s1[j - 1]) == 1)
		j--;
	new = (char *)malloc((j - i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < j)
		new[k++] = s1[i++];
	new[k] = '\0';
	return (new);
}
