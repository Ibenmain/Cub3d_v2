/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:15:41 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/05 16:02:03 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		size_s1;
	int		size_s2;
	char	*new;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	new = (char *)malloc((size_s1 + size_s2) + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (i < size_s1)
	{
		new[i] = s1[i];
		i++;
	}
	while (j < size_s2)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
